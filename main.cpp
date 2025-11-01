#include "Client.hpp"
#include "include/Sender.hpp"
#include "string"

using std::string_literals::operator ""s;

Message GetTestMessage() {
    return Message {
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
                    .label = "label"s,
                }
            }
        }
    };
}

int main() {
    Client client("https://vk.com");

    Sender sender(&client, 10);
    sender.Start();
    sender.QueueMessage(GetTestMessage(), [](const httplib::Result& response) {
        std::cout << response.error() << std::endl;
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}
