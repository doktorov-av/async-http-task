# Async http

## Requirements

This project provides 2 classes and 1 interface that are aimed to fulfill such requirements:

1. It should realize non-blocking sending of REST messages using cpp-httplib and nlohman-json
2. It should contain message queue with limit defined in constructor
3. Optional: realize as singleton [not done]

| Property        | Value               |
|-----------------|---------------------|
| Target endpoint | /api/photos         |
| Method          | POST                |
| Content-Type    | multipart/form-data |

Form fields:

### Image

File [for simplicity - vector of random bytes]

### Payload Json

Serialized message struct that looks like so:

```c++
struct Object
{
    float x_c; // центр бокса по X
    float y_c; // центр по Y
    float width; // ширина
    float height; // высота
    std::string label; // класс объекта
};

struct Message
{
    double shot_lat; // широта места съёмки
    double shot_lon; // долгота места съёмки
    std::vector<Object> objects;
};
```

## Usage

```c++
    Client client(/* api url */);
    Sender sender(&client, 10 /* size of queue */ );
    sender.Start();

    sender.QueueMessage(msg, [](const httplib::Result& result) {
        // handle response    
    });

    // do other stuff
```





