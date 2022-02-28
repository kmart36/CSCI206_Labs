#RISCV assembly double_value

.text
.globl double_value

double_value:
# a0 - parameter to be doubled
# a0 - return value

	add a0, a0, a0
	jr ra