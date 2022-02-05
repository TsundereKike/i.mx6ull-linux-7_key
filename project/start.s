.global _start

.global _bss_start
_bss_start:
    .word __bss_start

.global _bss_end
_bss_end:
    .word __bss_end


_start:
    /* 设置处理器进入SVC模式*/
    mrs r0, cpsr            /*读取cpsr到r0 */
    bic r0, r0, #0x1f       /*清除cpsr到bit4-0 */
    orr r0, r0, #0x13       /*使用SVC模式 */
    msr cpsr, r0           /*将r0写入到cpsr */

    /*清除BSS段 */
    ldr r0, _bss_start
    ldr r1, _bss_end
    mov r2, #0
bss_loop:
    stmia r0!, {r2}
    cmp r0, r1      /*比较r0和r1寄存器里的值 */
    ble bss_loop    /*如果r0地址小于等于r1，继续清除bss段 */

    /*设置SP指针 */
    ldr sp, =0x80200000
    b main          /*跳转到main函数 */
