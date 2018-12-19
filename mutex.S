  .section      .text
  .align 2
  .global mutex_acquire
mutex_acquire:
	li a1, 1
	// mutex passed as parameter in a0
try:
	amoswap.w.aq a1, a1, (a0)
	bnez a1, try
	addi a0, x0, 0
	ret

  .section      .text
  .align 2
  .global mutex_release
mutex_release:
	amoswap.w.rl x0, x0, (a0)
	ret
