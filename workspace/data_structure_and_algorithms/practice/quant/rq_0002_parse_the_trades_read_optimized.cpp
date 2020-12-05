#include <cstdlib>

#include <string>
#include <fstream>
#include <ctype.h>
#include <iomanip>

#include <iostream>


class Packet {
public:
    enum TYPE {
        TRADE = 'T',
        QUOTE = 'Q'
    };

    struct PacketHeader {
        uint16_t length;
        uint16_t num_market_updates;
    };

    struct SegmentHeader {
        static const size_t LENGTH = 8;

        uint16_t length;
        char type;
        char symbol[6];
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
            return *reinterpret_cast<uint16_t *>(&data[0]);
        }

        double GetPrice(void) {
            return *reinterpret_cast<uint64_t *>(&data[2]) / 10000.0;
        }
    };

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

    static void ReadPacketHeader(std::ifstream &in, PacketHeader &header) {
        in.read(reinterpret_cast<char *>(&header), sizeof(header));

        header.length = ntoh<uint16_t>(header.length); 
        header.num_market_updates = ntoh<uint16_t>(header.num_market_updates);   
    }

    static void ReadSegmentHeader(std::ifstream &in, SegmentHeader &header) {
        in.read(reinterpret_cast<char *>(&header), SegmentHeader::LENGTH);

        header.length = ntoh<uint16_t>(header.length);   

        // set string terminator:
        for (size_t i = 0; i < 6; ++i) {
            if ( isspace(header.symbol[i]) ) {
                header.symbol[i] = '\0';
                break;
            }
        }
    }

    static void ReadSegmentTrade(std::ifstream &in, Trade &segment) {
        in.read(reinterpret_cast<char *>(&segment), Trade::LENGTH);

        *reinterpret_cast<uint16_t *>(&segment.data[0]) = ntoh<uint16_t>(
            *reinterpret_cast<uint16_t *>(&segment.data[0])
        ); 
        *reinterpret_cast<uint64_t *>(&segment.data[2]) = ntoh<uint64_t>(
            *reinterpret_cast<uint64_t *>(&segment.data[2])
        );   
    }

    static void Parse(const std::string &input_filename, std::string output_filename) {
        std::ifstream in(input_filename, std::ios::binary);
        std::ofstream out(output_filename);

        // read header, 1 read operation:
        PacketHeader packet_header;
        ReadPacketHeader(in, packet_header);

        // read data segments:
        SegmentHeader segment_header;
        Trade trade;
        size_t displacement = 0;
        for (uint16_t i = 0; i < packet_header.num_market_updates; ++i) {
            // read segment header, 1 read operation:
            ReadSegmentHeader(in, segment_header);
            
            switch ( segment_header.type ) {
                case TYPE::QUOTE:
                    displacement = segment_header.length - 8 - sizeof(Quote);
                    break;
                case TYPE::TRADE:
                    // parse:
                    ReadSegmentTrade(in, trade);
                    // write:
                    out << 100 * trade.GetSize() << " " 
                        << segment_header.symbol << " @ " 
                        << std::fixed << std::setprecision(2) << trade.GetPrice()
                        << std::endl;
                    displacement = segment_header.length - 8 - sizeof(Trade);
                    break;
                default:
                    break;
            }

            // move to next segment:
            in.seekg(
                displacement, std::ios::cur
            );
        }

        out.close();
        in.close();
    }
};

int main() {
    std::string input_filename("../data/rq_0001_parse_the_trades.dat");
    std::string output_filename("trades.txt");

    Packet::Parse(input_filename, output_filename);

    return EXIT_SUCCESS;
}