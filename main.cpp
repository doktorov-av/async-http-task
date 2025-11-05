#include "Client.hpp"
#include "include/Sender.hpp"
#include "string"

int main() {
    Client client("localhost:8080");
    Sender sender(&client, 10);
    sender.Start();

    const auto msg = Message {
        .image = {0x12, 0x21, 0xFF, 0x13},
        .payload = {
            .shotLat = 10,
            .shotLon = 20,
            .objects = {
                Object{
                    .x_c = 1,
                    .y_c = 1,
                    .width = 100,
                    .height = 100,
                    .label = "label",
                }
            }
        }
    };

    bool ok = sender.QueueMessage(msg, [](const httplib::Result& result) {
        // this callback is executed not in main thread, so user must ensure handling is thread safe
        std::cout << "Got response from server: " << result.error() << ", thread id = " << std::this_thread::get_id() << '\n';
    });

    if (!ok) {
        std::cerr << "Couldn't queue message\n";
    } else {
    std::cout << "Sent message, doing other work on thread " << std::this_thread::get_id() << '\n';
    }


    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}
