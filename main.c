#include <stdio.h>
#include "regions/regions.h"

int main() {

    current_file *f = create_parser("../MalhaAereaUSA.txt");
    regions *re = create_regions(f);
    return 0;
}
