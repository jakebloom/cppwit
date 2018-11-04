#include <assert.h>
#include <stdlib.h>

#include "Wit.h"
#include "WitResp.h"

int main(int argc, char *argv[]) {
    assert(argc == 2);
    Wit client = Wit(argv[1]);

    printf("Testing message API with \"Turn on the lights\":\n");
    WitResp res = client.message("Turn on the lights");
    res.print();

    printf("Testing speech API with \"Turn on the lights to fifty percent\":\n");
    FILE * fd = fopen("test.wav", "rb");
    res = client.speech(fd);
    res.print();
    return EXIT_SUCCESS;
}