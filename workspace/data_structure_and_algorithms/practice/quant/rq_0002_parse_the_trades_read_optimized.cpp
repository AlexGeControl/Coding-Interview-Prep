#include <cstdlib>

#include <string>
#include <fstream>
#include <ctype.h>
#include <iomanip>

#include <iostream>

#include <boost/program_options.hpp>


class Packet {
public:
    enum TYPE {
        TRADE = 'T',
        QUOTE = 'Q'
    };

    struct PacketHeader {
        static const size_t LENGTH = 4;

        uint16_t length;
        uint16_t num_market_updates;
    };

    struct SegmentHeader {
        static const size_t LENGTH = 8;

        uint16_t length;
        char type;
        char symbol[5];
    };

    struct Quote {
        static const size_t LENGTH = 8;

        uint16_t level;
        uint16_t size;
        uint64_t price;
    };

    struct Trade {
        static const size_t LENGTH = 10;

        char data[10];

        uint32_t GetSize(void) {
            return 100 * (*reinterpret_cast<uint16_t *>(&data[0]));
        }

        double GetPrice(void) {
            return *reinterpret_cast<uint64_t *>(&data[2]) / 10000.0;
        }
    };

    explicit Packet(const std::string &input_filename) {
        // read as binary file:
        std::ifstream in(input_filename, std::ios::binary);
        
        // read header:
        ReadPacketHeader(in);

        // read data:
        ReadPacketData(in);
    }

    ~Packet() { 
        if ( nullptr != data_ ) delete [] data_; 
    }

    void WriteTrades(const std::string &output_filename) {
        std::ofstream out(output_filename);

        // read data segments:
        SegmentHeader *segment_header = nullptr;
        Trade *trade = nullptr;
        size_t offset = 0;
        for (uint16_t i = 0; i < header_.num_market_updates; ++i) {
            // read segment header:
            segment_header = ReadSegmentHeader(offset);
            
            switch ( segment_header->type ) {
                case TYPE::QUOTE:
                    break;
                case TYPE::TRADE:
                    // parse:
                    trade = ReadSegmentTrade(offset + SegmentHeader::LENGTH);
                    // write:
                    WriteTrade(
                        out, 
                        trade->GetSize(), segment_header->symbol, trade->GetPrice()
                    );
                    break;
                default:
                    break;
            }

            offset += segment_header->length;
        }

        out.close();
    }

private:
    PacketHeader header_;

    char *data_ = nullptr;

    /**
     * @brief  parse data in network order
     * @param  in, input file stream
     * @param  data, output data
     * @return true if success false otherwise
     */
    template <typename T>
    static T ntoh(const T &in) {
        const size_t N = sizeof(in);

        T out;
        
        // ntoh:
        for (size_t i = 0; i < N; ++i) {
            *(reinterpret_cast<char *>(&out) + i) = *(
                reinterpret_cast<const char *>(&in) + N - 1 - i
            );
        }

        return out;
    }

    static void WriteTrade(std::ofstream &out, const int size, const char symbol[], const double price) {
        out << size << " " << symbol << " @ " 
            << std::fixed << std::setprecision(2) << price
            << std::endl;
    }

    /**
     * @brief  parse packet header
     * @param  in, input file stream
     * @return void
     */
    void ReadPacketHeader(std::ifstream &in) {
        in.read(reinterpret_cast<char *>(&header_), PacketHeader::LENGTH);

        header_.length = ntoh<uint16_t>(header_.length); 
        header_.num_market_updates = ntoh<uint16_t>(header_.num_market_updates);   
    }

    /**
     * @brief  parse packet data
     * @param  in, input file stream
     * @return void
     */
    void ReadPacketData(std::ifstream &in) {
        const size_t N = header_.length - PacketHeader::LENGTH;

        data_ = new char[N];

        in.read(reinterpret_cast<char *>(data_), N);
    }

    /**
     * @brief  parse segment header
     * @param  offset, data offset
     * @return pointer to current segment header
     */
    SegmentHeader * ReadSegmentHeader(const size_t offset) {
        SegmentHeader *header = reinterpret_cast<SegmentHeader *>(data_ + offset);

        // set string terminator:
        for (size_t i = 0; i < 6; ++i) {
            if ( isspace(header->symbol[i]) ) {
                header->symbol[i] = '\0';
                break;
            }
        }

        header->length = ntoh<uint16_t>(header->length);   

        return header;
    }

    /**
     * @brief  parse trade segment
     * @param  offset, data offset
     * @return pointer to current trade segment
     */
    Trade *ReadSegmentTrade(const size_t offset) {
        Trade *trade = reinterpret_cast<Trade *>(data_ + offset);

        *reinterpret_cast<uint16_t *>(&trade->data[0]) = ntoh<uint16_t>(
            *reinterpret_cast<uint16_t *>(&trade->data[0])
        ); 
        *reinterpret_cast<uint64_t *>(&trade->data[2]) = ntoh<uint64_t>(
            *reinterpret_cast<uint64_t *>(&trade->data[2])
        );   

        return trade;
    }
};

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
    // parse command line options:
    try
    {   
        // command line arguments:
        po::options_description desc{"Parse trades out of market updates"};
        desc.add_options()
            ("help,h", "Show help info")
            ("input,i", po::value<std::string>(), "Input market update")
            ("output,o",  po::value<std::string>(), "Output trade records");
        po::positional_options_description pos;
        pos.add("input", 2);

        po::variables_map vm;
        po::store(
            po::command_line_parser(argc, argv).options(desc).positional(pos).run(), 
            vm
        );
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
        } else {
            // parse arguments:
            const std::string &input = vm["input"].as<std::string>();
            const std::string &output = vm["output"].as<std::string>();

            std::cout << "Command-Line Arguments:" << std::endl;
            std::cout << "\tinput: " << input << std::endl;
            std::cout << "\toutput: " << output << std::endl;

            // load packet:
            Packet packet(input);

            // write trades
            packet.WriteTrades(output);
        }
    }
    catch (const boost::program_options::error &ex)
    {
        std::cerr << ex.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}