//
// Lazy Pirate server
// Binds REQ socket to tcp://*:5555
// Like hwserver except:
// - echoes request as-is
// - randomly runs slowly, or exits to simulate a crash.
//
#include "zhelpers.hpp"

namespace {
    constexpr int MAX_RESPONSE = 3000;
    bool isok(const int cycles) {
        return cycles > MAX_RESPONSE && within(MAX_RESPONSE) == 0;
    }
    
}

int main() {
    srandom((unsigned)time(NULL));

    zmq::context_t context(1);
    zmq::socket_t server(context, ZMQ_REP);
    server.bind("tcp://*:5555");

    int cycles = 0;
    
    while (1) {
        std::string request = s_recv(server);
        cycles++;

        // Simulate various problems, after a few cycles
        if (isok(cycles)) {
            std::cout << "I: simulating a crash" << std::endl;
            break;
        } else if (isok(cycles)) {
            std::cout << "I: simulating CPU overload" << std::endl;
            sleep(2);
        }
        
        std::cout << "I: normal request: " << request << "\n";
        sleep(1); // Do some heavy work
        s_send(server, request);
    }
    return 0;
}
