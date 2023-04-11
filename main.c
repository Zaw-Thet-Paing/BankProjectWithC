/*
 *Personal Account
 * Wallet Capacity : 1000000, Limit Per Day : 100000
 *
 * Business Account
 * Wallet Capacity : 10000000, Limit Per Day : 1000000
 */

#include "stdio.h"
#include "z_library.h"
#include "bank.h"

int main() {

    space_counter();
    loading_all_data_from_file();
    printing_all_data();
    welcome();

//    printf("Total %u", get_total_amount_of_same_day(1, 1000));

    return 0;
}
