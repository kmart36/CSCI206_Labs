# double.s
#
# 2021-08-14
# by Xiannong Meng
# Example of procedure use, double
# for CSCI 206
.text

    addi  a0, zero, 4
    jal   double         # a0 = result

    addi  a0, zero, 15
    jal   double
        
    li    a7, 10         # call for exit
    ecall
    
double:
    # a0 - parameter to be doubled
    # a0 - the squared value to return

    addi sp, sp, -4
    sw   ra, 0(sp)
    add a0, a0, a0       # add a0 to itself, save in a0
    jal extra
    lw ra, 0(sp)
    addi sp, sp, 4
    jr  ra
extra:
    jr ra
