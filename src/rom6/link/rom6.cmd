/* ROM6 linker command skeleton (TMS320C542, single-page, TI COFF).
 * Facts: docs/01-memory-map.md. IPTR=0x1FF -> vectors at 0xFF80 (mask ROM).
 * PMST.OVLY=1 maps DARAM over program space [0x0080, 0x2000) on ROM6
 * (ROM4 ovly_end is 0x2800 with banked XPC paging; ROM6 is single-page).
 * HPI RAM is dual-ported DARAM: DSP 0x0800-0x0FFF <-> MCU 0x10000-0x10FFF.
 * Not yet used for a full link: modules recombine per-span via
 * tools/recombine.py (; ORIGIN headers). This file records the target
 * layout so per-span origins stay link-consistent as coverage grows.
 */
MEMORY
{
  PAGE 0: /* program */
    OVLYRAM  : origin = 0x0080, length = 0x1F80  /* uploaded pages + RTOS */
    PROMLOW  : origin = 0x2800, length = 0x8800  /* low PROM routines */
    PROMHIGH : origin = 0xB000, length = 0x4D00  /* mask ROM routines/tables */
    BRANCH   : origin = 0xFD00, length = 0x0280  /* PROM branch table */
    VECS     : origin = 0xFF80, length = 0x0080  /* reset + IVT, mask ROM */
  PAGE 1: /* data */
    DARAM    : origin = 0x0080, length = 0x1F80
    HPIRAM   : origin = 0x0800, length = 0x0800  /* dual-port, MCU window */
}
