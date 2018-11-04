# cppwit
A [wit.ai](https://wit.ai) client for c++, allowing embedded devices to do NLP efficiently.

## Motivation
wit.ai is a great, open source tool that allows you to send text or speech to the wit.ai server, and receive back a list of entities and values. Currently, [pywit](https://github.com/wit-ai/pywit) provides an API for Python, however there is no API for lower level languages, which would be particularly useful for cheaper and embedded devices.

cppwit fills this gap, providing a simple API for usage of wit in embedded devices (or non-embedded devices where the developer chooses to run C/C++!)

## Dependencies
We rely on [Niels Lohmann's JSON library](https://github.com/nlohmann/json) to parse the json response from the wit.ai server. On OSX you can download it using homebrew, or you can copy his [json.hpp](https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp) file to `/usr/local/include/nlohmann`.


## Installation
```
> git clone https://github.com/jakebloom/cppwit.git
...
> cd cppwit
> # to install a dynamic library
> make dynamic # might need sudo
> # to create a static library
> make static # result will be in ./bin/libWit.a
```

## Using the Dynamic Library
```
#include <Wit.h>
#include <WitResp.h>

int main(int argc, char* argv) {
    Wit client = Wit("YOUR_WIT_API_TOKEN");
    WitResp res = client.message("Turn on the lights");
    res.print();
    return 0;
}
```
### Output:

```
ID: 1gaLyFYybXzh8hnLt
Text: Turn on the lights
Entity: device
	Confidence: 1.000000
	Type: value
	Value: light

Entity: on_off
	Confidence: 0.985204
	Type:
	Value: on
```

## Using the Static Library
We can use the same code as the dynamic library and expect the same output, however we must compile the static library together with the binary:
```
> g++ -o main main.c -lWit
> ./main
```

## Creator's Note
All contributions to this repository are done so in a personal capacity, not on behalf of my employer.