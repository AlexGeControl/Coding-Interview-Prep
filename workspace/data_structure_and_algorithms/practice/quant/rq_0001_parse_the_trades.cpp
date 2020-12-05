#include <cstdlib>

#include <string>
#include <fstream>
#include <netinet/in.h>

#include <vector>

#include <iomanip>

#include <iostream>


class Packet {
public:
    enum TYPE {
        TRADE = 'T',
        QUOTE = 'Q'
    };

    struct Quote {
        static const size_t SEGMENT_LENGH = 18;

        char symbol[6];
        uint16_t level;
        uint16_t size;
        uint64_t price;
    };

    struct Trade {
        static const size_t SEGMENT_LENGH = 16;

        char symbol[6];
        uint16_t size;
        uint64_t price;
    };

    Packet(const std::string &input_filename) {
        std::ifstream in(input_filename, std::ios::in | std::ios::binary);

        // parse packet length:
        Get<uint16_t>(in, packet_length_);
        // parse num. market updates:
        Get<uint16_t>(in, num_market_updates_);
        
        //
        // parse updates:
        //
        uint8_t data_type; uint16_t data_length;
        Quote quote; Trade trade;
        for ( uint16_t i = 0; i < num_market_updates_; ++i) {
            GetDataType(in, data_type, data_length);

            switch (data_type) {
                case TYPE::QUOTE:
                    GetQuote(in, quote, data_length);
                    quotes_.push_back(quote);
                    break;
                case TYPE::TRADE:
                    GetTrade(in, trade, data_length);
                    trades_.push_back(trade);
                    break;
                default:
                    break;
            }
        }

        // close input file:
        in.close();
    }

    bool WriteTrades(const std::string &output_filename) {
        std::ofstream out(output_filename);

        for (const Trade &trade: trades_) {
            out << trade.size << " " << trade.symbol << " @ " << std::fixed << std::setprecision(2) << trade.price / 10000.0 << std::endl;
        }

        out.close();

        return true;
    }

private:
    uint16_t packet_length_ = 0;
    uint16_t num_market_updates_ = 0;

    std::vector<Quote> quotes_;
    std::vector<Trade> trades_;

    /**
     * @brief  parse data in network order
     * @param  in, input file stream
     * @param  data, output data
     * @return true if success false otherwise
     */
    template <typename T>
    bool Get(std::ifstream &in, T &data) {
        const size_t N = sizeof(data);

        T data_in_network_order;
        if ( in.read(reinterpret_cast<char *>(&data_in_network_order), N)) {
            // ntoh:
            for (size_t i = 0; i < N; ++i) {
                *(reinterpret_cast<char *>(&data) + i) = *(
                    reinterpret_cast<char *>(&data_in_network_order) + N - 1 - i
                );
            }

            return true;
        }

        return false;
    }

    /**
     * @brief  parse data in network order of given size
     * @param  in, input file stream
     * @param  data, output data
     * @return true if success false otherwise
     */
    template <typename T>
    bool Get(std::ifstream &in, T &data, const size_t size) {
        if ( in.read(reinterpret_cast<char *>(&data), size)) {
            return true;
        }

        return false;
    }

    /**
     * @brief  parse data segment length & type
     * @param  in, input file stream
     * @param  type, output data type
     * @param  length, output data length
     * @return true if success false otherwise
     */
    bool GetDataType(std::ifstream &in, uint8_t &type, uint16_t &length) {
        if ( Get<uint16_t>(in, length) && Get<uint8_t>(in, type) ) {
            return true;
        }

        return false;
    }

    /**
     * @brief  parse trade segment
     * @param  in, input file stream
     * @param  trade, output trade record
     * @return true if success false otherwise
     */
    bool GetTrade(std::ifstream &in, Trade &trade, const uint16_t segment_length) {
        if (
            Get(in, trade.symbol, 5) &&       // symbol
            Get<uint16_t>(in, trade.size) &&  // size
            Get<uint64_t>(in, trade.price)    // price
        ) {
            // add string terminator:
            trade.symbol[5] = '\0';

            // skip dynamic data:
            in.seekg(
                segment_length - 2 - Trade::SEGMENT_LENGH, std::ios::cur
            );
            return true;
        }

        return false;
    };

    /**
     * @brief  parse quote segment
     * @param  in, input file stream
     * @param  quote, output quote record
     * @return true if success false otherwise
     */
    bool GetQuote(std::ifstream &in, Quote &quote, const uint16_t segment_length) {
        if (
            Get(in, quote.symbol, 5) &&       // symbol
            Get<uint16_t>(in, quote.level) && // level
            Get<uint16_t>(in, quote.size) &&  // size
            Get<uint64_t>(in, quote.price)    // price
        ) {
            // add string terminator:
            quote.symbol[5] = '\0';

            // skip dynamic data:
            in.seekg(
                segment_length - 2 - Quote::SEGMENT_LENGH, std::ios::cur
            );
            return true;
        }

        return false;
    };
};

int main() {
    std::string input_filename("../data/rq_0001_parse_the_trades.dat");

    Packet packet(input_filename);

    packet.WriteTrades("trades.txt");

    return EXIT_SUCCESS;
}