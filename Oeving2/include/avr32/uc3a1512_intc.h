/*****************************************************************************
 *
 * Copyright (C) 2008 Atmel Corporation
 * 
 * Model        : UC3A1512
 * Revision     : $Revision: 58751 $
 * Checkin Date : $Date: 2008-09-15 15:20:42 +0200 (Mon, 15 Sep 2008) $ 
 *
 ****************************************************************************/
#ifndef AVR32_UC3A1512_INTC_H_INCLUDED
#define AVR32_UC3A1512_INTC_H_INCLUDED

#include "avr32/abi.h"

#define AVR32_INTC_ICR0                                     0x0000020c
#define AVR32_INTC_ICR0_CAUSEGRP                                     0
#define AVR32_INTC_ICR0_CAUSEGRP_MASK                       0x0000003f
#define AVR32_INTC_ICR0_CAUSEGRP_OFFSET                              0
#define AVR32_INTC_ICR0_CAUSEGRP_SIZE                                6
#define AVR32_INTC_ICR0_MASK                                0x0000003f
#define AVR32_INTC_ICR0_RESETVALUE                          0x00000000
#define AVR32_INTC_ICR1                                     0x00000208
#define AVR32_INTC_ICR1_CAUSEGRP                                     0
#define AVR32_INTC_ICR1_CAUSEGRP_MASK                       0x0000003f
#define AVR32_INTC_ICR1_CAUSEGRP_OFFSET                              0
#define AVR32_INTC_ICR1_CAUSEGRP_SIZE                                6
#define AVR32_INTC_ICR1_MASK                                0x0000003f
#define AVR32_INTC_ICR1_RESETVALUE                          0x00000000
#define AVR32_INTC_ICR2                                     0x00000204
#define AVR32_INTC_ICR2_CAUSEGRP                                     0
#define AVR32_INTC_ICR2_CAUSEGRP_MASK                       0x0000003f
#define AVR32_INTC_ICR2_CAUSEGRP_OFFSET                              0
#define AVR32_INTC_ICR2_CAUSEGRP_SIZE                                6
#define AVR32_INTC_ICR2_MASK                                0x0000003f
#define AVR32_INTC_ICR2_RESETVALUE                          0x00000000
#define AVR32_INTC_ICR3                                     0x00000200
#define AVR32_INTC_ICR3_CAUSEGRP                                     0
#define AVR32_INTC_ICR3_CAUSEGRP_MASK                       0x0000003f
#define AVR32_INTC_ICR3_CAUSEGRP_OFFSET                              0
#define AVR32_INTC_ICR3_CAUSEGRP_SIZE                                6
#define AVR32_INTC_ICR3_MASK                                0x0000003f
#define AVR32_INTC_ICR3_RESETVALUE                          0x00000000
#define AVR32_INTC_IPR0                                     0x00000000
#define AVR32_INTC_IPR0_INTLEV                                      30
#define AVR32_INTC_IPR0_INTLEV_MASK                         0xc0000000
#define AVR32_INTC_IPR0_INTLEV_OFFSET                               30
#define AVR32_INTC_IPR0_INTLEV_SIZE                                  2
#define AVR32_INTC_IPR0_MASK                                0xc0003fff
#define AVR32_INTC_IPR0_OFFSET                                       0
#define AVR32_INTC_IPR0_OFFSET_MASK                         0x00003fff
#define AVR32_INTC_IPR0_OFFSET_OFFSET                                0
#define AVR32_INTC_IPR0_OFFSET_SIZE                                 14
#define AVR32_INTC_IPR0_RESETVALUE                          0x00000000
#define AVR32_INTC_IPR1                                     0x00000004
#define AVR32_INTC_IPR10                                    0x00000028
#define AVR32_INTC_IPR10_INTLEV                                     30
#define AVR32_INTC_IPR10_INTLEV_MASK                        0xc0000000
#define AVR32_INTC_IPR10_INTLEV_OFFSET                              30
#define AVR32_INTC_IPR10_INTLEV_SIZE                                 2
#define AVR32_INTC_IPR10_MASK                               0xc0003fff
#define AVR32_INTC_IPR10_OFFSET                                      0
#define AVR32_INTC_IPR10_OFFSET_MASK                        0x00003fff
#define AVR32_INTC_IPR10_OFFSET_OFFSET                               0
#define AVR32_INTC_IPR10_OFFSET_SIZE                                14
#define AVR32_INTC_IPR10_RESETVALUE                         0x00000000
#define AVR32_INTC_IPR11                                    0x0000002c
#define AVR32_INTC_IPR11_INTLEV                                     30
#define AVR32_INTC_IPR11_INTLEV_MASK                        0xc0000000
#define AVR32_INTC_IPR11_INTLEV_OFFSET                              30
#define AVR32_INTC_IPR11_INTLEV_SIZE                                 2
#define AVR32_INTC_IPR11_MASK                               0xc0003fff
#define AVR32_INTC_IPR11_OFFSET                                      0
#define AVR32_INTC_IPR11_OFFSET_MASK                        0x00003fff
#define AVR32_INTC_IPR11_OFFSET_OFFSET                               0
#define AVR32_INTC_IPR11_OFFSET_SIZE                                14
#define AVR32_INTC_IPR11_RESETVALUE                         0x00000000
#define AVR32_INTC_IPR12                                    0x00000030
#define AVR32_INTC_IPR12_INTLEV                                     30
#define AVR32_INTC_IPR12_INTLEV_MASK                        0xc0000000
#define AVR32_INTC_IPR12_INTLEV_OFFSET                              30
#define AVR32_INTC_IPR12_INTLEV_SIZE                                 2
#define AVR32_INTC_IPR12_MASK                               0xc0003fff
#define AVR32_INTC_IPR12_OFFSET                                      0
#define AVR32_INTC_IPR12_OFFSET_MASK                        0x00003fff
#define AVR32_INTC_IPR12_OFFSET_OFFSET                               0
#define AVR32_INTC_IPR12_OFFSET_SIZE                                14
#define AVR32_INTC_IPR12_RESETVALUE                         0x00000000
#define AVR32_INTC_IPR13                                    0x00000034
#define AVR32_INTC_IPR13_INTLEV                                     30
#define AVR32_INTC_IPR13_INTLEV_MASK                        0xc0000000
#define AVR32_INTC_IPR13_INTLEV_OFFSET                              30
#define AVR32_INTC_IPR13_INTLEV_SIZE                                 2
#define AVR32_INTC_IPR13_MASK                               0xc0003fff
#define AVR32_INTC_IPR13_OFFSET                                      0
#define AVR32_INTC_IPR13_OFFSET_MASK                        0x00003fff
#define AVR32_INTC_IPR13_OFFSET_OFFSET                               0
#define AVR32_INTC_IPR13_OFFSET_SIZE                                14
#define AVR32_INTC_IPR13_RESETVALUE                         0x00000000
#define AVR32_INTC_IPR14                                    0x00000038
#define AVR32_INTC_IPR14_INTLEV                                     30
#define AVR32_INTC_IPR14_INTLEV_MASK                        0xc0000000
#define AVR32_INTC_IPR14_INTLEV_OFFSET                              30
#define AVR32_INTC_IPR14_INTLEV_SIZE                                 2
#define AVR32_INTC_IPR14_MASK                               0xc0003fff
#define AVR32_INTC_IPR14_OFFSET                                      0
#define AVR32_INTC_IPR14_OFFSET_MASK                        0x00003fff
#define AVR32_INTC_IPR14_OFFSET_OFFSET                               0
#define AVR32_INTC_IPR14_OFFSET_SIZE                                14
#define AVR32_INTC_IPR14_RESETVALUE                         0x00000000
#define AVR32_INTC_IPR15                                    0x0000003c
#define AVR32_INTC_IPR15_INTLEV                                     30
#define AVR32_INTC_IPR15_INTLEV_MASK                        0xc0000000
#define AVR32_INTC_IPR15_INTLEV_OFFSET                              30
#define AVR32_INTC_IPR15_INTLEV_SIZE                                 2
#define AVR32_INTC_IPR15_MASK                               0xc0003fff
#define AVR32_INTC_IPR15_OFFSET                                      0
#define AVR32_INTC_IPR15_OFFSET_MASK                        0x00003fff
#define AVR32_INTC_IPR15_OFFSET_OFFSET                               0
#define AVR32_INTC_IPR15_OFFSET_SIZE                                14
#define AVR32_INTC_IPR15_RESETVALUE                         0x00000000
#define AVR32_INTC_IPR16                                    0x00000040
#define AVR32_INTC_IPR16_INTLEV                                     30
#define AVR32_INTC_IPR16_INTLEV_MASK                        0xc0000000
#define AVR32_INTC_IPR16_INTLEV_OFFSET                              30
#define AVR32_INTC_IPR16_INTLEV_SIZE                                 2
#define AVR32_INTC_IPR16_MASK                               0xc0003fff
#define AVR32_INTC_IPR16_OFFSET                                      0
#define AVR32_INTC_IPR16_OFFSET_MASK                        0x00003fff
#define AVR32_INTC_IPR16_OFFSET_OFFSET                               0
#define AVR32_INTC_IPR16_OFFSET_SIZE                                14
#define AVR32_INTC_IPR16_RESETVALUE                         0x00000000
#define AVR32_INTC_IPR17                                    0x00000044
#define AVR32_INTC_IPR17_INTLEV                                     30
#define AVR32_INTC_IPR17_INTLEV_MASK                        0xc0000000
#define AVR32_INTC_IPR17_INTLEV_OFFSET                              30
#define AVR32_INTC_IPR17_INTLEV_SIZE                                 2
#define AVR32_INTC_IPR17_MASK                               0xc0003fff
#define AVR32_INTC_IPR17_OFFSET                                      0
#define AVR32_INTC_IPR17_OFFSET_MASK                        0x00003fff
#define AVR32_INTC_IPR17_OFFSET_OFFSET                               0
#define AVR32_INTC_IPR17_OFFSET_SIZE                                14
#define AVR32_INTC_IPR17_RESETVALUE                         0x00000000
#define AVR32_INTC_IPR18                                    0x00000048
#define AVR32_INTC_IPR18_INTLEV                                     30
#define AVR32_INTC_IPR18_INTLEV_MASK                        0xc0000000
#define AVR32_INTC_IPR18_INTLEV_OFFSET                              30
#define AVR32_INTC_IPR18_INTLEV_SIZE                                 2
#define AVR32_INTC_IPR18_MASK                               0xc0003fff
#define AVR32_INTC_IPR18_OFFSET                                      0
#define AVR32_INTC_IPR18_OFFSET_MASK                        0x00003fff
#define AVR32_INTC_IPR18_OFFSET_OFFSET                               0
#define AVR32_INTC_IPR18_OFFSET_SIZE                                14
#define AVR32_INTC_IPR18_RESETVALUE                         0x00000000
#define AVR32_INTC_IPR19                                    0x0000004c
#define AVR32_INTC_IPR19_INTLEV                                     30
#define AVR32_INTC_IPR19_INTLEV_MASK                        0xc0000000
#define AVR32_INTC_IPR19_INTLEV_OFFSET                              30
#define AVR32_INTC_IPR19_INTLEV_SIZE                                 2
#define AVR32_INTC_IPR19_MASK                               0xc0003fff
#define AVR32_INTC_IPR19_OFFSET                                      0
#define AVR32_INTC_IPR19_OFFSET_MASK                        0x00003fff
#define AVR32_INTC_IPR19_OFFSET_OFFSET                               0
#define AVR32_INTC_IPR19_OFFSET_SIZE                                14
#define AVR32_INTC_IPR19_RESETVALUE                         0x00000000
#define AVR32_INTC_IPR1_INTLEV                                      30
#define AVR32_INTC_IPR1_INTLEV_MASK                         0xc0000000
#define AVR32_INTC_IPR1_INTLEV_OFFSET                               30
#define AVR32_INTC_IPR1_INTLEV_SIZE                                  2
#define AVR32_INTC_IPR1_MASK                                0xc0003fff
#define AVR32_INTC_IPR1_OFFSET                                       0
#define AVR32_INTC_IPR1_OFFSET_MASK                         0x00003fff
#define AVR32_INTC_IPR1_OFFSET_OFFSET                                0
#define AVR32_INTC_IPR1_OFFSET_SIZE                                 14
#define AVR32_INTC_IPR1_RESETVALUE                          0x00000000
#define AVR32_INTC_IPR2                                     0x00000008
#define AVR32_INTC_IPR2_INTLEV                                      30
#define AVR32_INTC_IPR2_INTLEV_MASK                         0xc0000000
#define AVR32_INTC_IPR2_INTLEV_OFFSET                               30
#define AVR32_INTC_IPR2_INTLEV_SIZE                                  2
#define AVR32_INTC_IPR2_MASK                                0xc0003fff
#define AVR32_INTC_IPR2_OFFSET                                       0
#define AVR32_INTC_IPR2_OFFSET_MASK                         0x00003fff
#define AVR32_INTC_IPR2_OFFSET_OFFSET                                0
#define AVR32_INTC_IPR2_OFFSET_SIZE                                 14
#define AVR32_INTC_IPR2_RESETVALUE                          0x00000000
#define AVR32_INTC_IPR3                                     0x0000000c
#define AVR32_INTC_IPR3_INTLEV                                      30
#define AVR32_INTC_IPR3_INTLEV_MASK                         0xc0000000
#define AVR32_INTC_IPR3_INTLEV_OFFSET                               30
#define AVR32_INTC_IPR3_INTLEV_SIZE                                  2
#define AVR32_INTC_IPR3_MASK                                0xc0003fff
#define AVR32_INTC_IPR3_OFFSET                                       0
#define AVR32_INTC_IPR3_OFFSET_MASK                         0x00003fff
#define AVR32_INTC_IPR3_OFFSET_OFFSET                                0
#define AVR32_INTC_IPR3_OFFSET_SIZE                                 14
#define AVR32_INTC_IPR3_RESETVALUE                          0x00000000
#define AVR32_INTC_IPR4                                     0x00000010
#define AVR32_INTC_IPR4_INTLEV                                      30
#define AVR32_INTC_IPR4_INTLEV_MASK                         0xc0000000
#define AVR32_INTC_IPR4_INTLEV_OFFSET                               30
#define AVR32_INTC_IPR4_INTLEV_SIZE                                  2
#define AVR32_INTC_IPR4_MASK                                0xc0003fff
#define AVR32_INTC_IPR4_OFFSET                                       0
#define AVR32_INTC_IPR4_OFFSET_MASK                         0x00003fff
#define AVR32_INTC_IPR4_OFFSET_OFFSET                                0
#define AVR32_INTC_IPR4_OFFSET_SIZE                                 14
#define AVR32_INTC_IPR4_RESETVALUE                          0x00000000
#define AVR32_INTC_IPR5                                     0x00000014
#define AVR32_INTC_IPR5_INTLEV                                      30
#define AVR32_INTC_IPR5_INTLEV_MASK                         0xc0000000
#define AVR32_INTC_IPR5_INTLEV_OFFSET                               30
#define AVR32_INTC_IPR5_INTLEV_SIZE                                  2
#define AVR32_INTC_IPR5_MASK                                0xc0003fff
#define AVR32_INTC_IPR5_OFFSET                                       0
#define AVR32_INTC_IPR5_OFFSET_MASK                         0x00003fff
#define AVR32_INTC_IPR5_OFFSET_OFFSET                                0
#define AVR32_INTC_IPR5_OFFSET_SIZE                                 14
#define AVR32_INTC_IPR5_RESETVALUE                          0x00000000
#define AVR32_INTC_IPR6                                     0x00000018
#define AVR32_INTC_IPR6_INTLEV                                      30
#define AVR32_INTC_IPR6_INTLEV_MASK                         0xc0000000
#define AVR32_INTC_IPR6_INTLEV_OFFSET                               30
#define AVR32_INTC_IPR6_INTLEV_SIZE                                  2
#define AVR32_INTC_IPR6_MASK                                0xc0003fff
#define AVR32_INTC_IPR6_OFFSET                                       0
#define AVR32_INTC_IPR6_OFFSET_MASK                         0x00003fff
#define AVR32_INTC_IPR6_OFFSET_OFFSET                                0
#define AVR32_INTC_IPR6_OFFSET_SIZE                                 14
#define AVR32_INTC_IPR6_RESETVALUE                          0x00000000
#define AVR32_INTC_IPR7                                     0x0000001c
#define AVR32_INTC_IPR7_INTLEV                                      30
#define AVR32_INTC_IPR7_INTLEV_MASK                         0xc0000000
#define AVR32_INTC_IPR7_INTLEV_OFFSET                               30
#define AVR32_INTC_IPR7_INTLEV_SIZE                                  2
#define AVR32_INTC_IPR7_MASK                                0xc0003fff
#define AVR32_INTC_IPR7_OFFSET                                       0
#define AVR32_INTC_IPR7_OFFSET_MASK                         0x00003fff
#define AVR32_INTC_IPR7_OFFSET_OFFSET                                0
#define AVR32_INTC_IPR7_OFFSET_SIZE                                 14
#define AVR32_INTC_IPR7_RESETVALUE                          0x00000000
#define AVR32_INTC_IPR8                                     0x00000020
#define AVR32_INTC_IPR8_INTLEV                                      30
#define AVR32_INTC_IPR8_INTLEV_MASK                         0xc0000000
#define AVR32_INTC_IPR8_INTLEV_OFFSET                               30
#define AVR32_INTC_IPR8_INTLEV_SIZE                                  2
#define AVR32_INTC_IPR8_MASK                                0xc0003fff
#define AVR32_INTC_IPR8_OFFSET                                       0
#define AVR32_INTC_IPR8_OFFSET_MASK                         0x00003fff
#define AVR32_INTC_IPR8_OFFSET_OFFSET                                0
#define AVR32_INTC_IPR8_OFFSET_SIZE                                 14
#define AVR32_INTC_IPR8_RESETVALUE                          0x00000000
#define AVR32_INTC_IPR9                                     0x00000024
#define AVR32_INTC_IPR9_INTLEV                                      30
#define AVR32_INTC_IPR9_INTLEV_MASK                         0xc0000000
#define AVR32_INTC_IPR9_INTLEV_OFFSET                               30
#define AVR32_INTC_IPR9_INTLEV_SIZE                                  2
#define AVR32_INTC_IPR9_MASK                                0xc0003fff
#define AVR32_INTC_IPR9_OFFSET                                       0
#define AVR32_INTC_IPR9_OFFSET_MASK                         0x00003fff
#define AVR32_INTC_IPR9_OFFSET_OFFSET                                0
#define AVR32_INTC_IPR9_OFFSET_SIZE                                 14
#define AVR32_INTC_IPR9_RESETVALUE                          0x00000000
#define AVR32_INTC_IRR0                                     0x00000100
#define AVR32_INTC_IRR0_IREQUEST0                                    0
#define AVR32_INTC_IRR0_IREQUEST0_MASK                      0x00000001
#define AVR32_INTC_IRR0_IREQUEST0_OFFSET                             0
#define AVR32_INTC_IRR0_IREQUEST0_SIZE                               1
#define AVR32_INTC_IRR0_MASK                                0x00000001
#define AVR32_INTC_IRR0_RESETVALUE                          0x00000000
#define AVR32_INTC_IRR1                                     0x00000104
#define AVR32_INTC_IRR10                                    0x00000128
#define AVR32_INTC_IRR10_IREQUEST320                                 0
#define AVR32_INTC_IRR10_IREQUEST320_MASK                   0x00000001
#define AVR32_INTC_IRR10_IREQUEST320_OFFSET                          0
#define AVR32_INTC_IRR10_IREQUEST320_SIZE                            1
#define AVR32_INTC_IRR10_MASK                               0x00000001
#define AVR32_INTC_IRR10_RESETVALUE                         0x00000000
#define AVR32_INTC_IRR11                                    0x0000012c
#define AVR32_INTC_IRR11_IREQUEST352                                 0
#define AVR32_INTC_IRR11_IREQUEST352_MASK                   0x00000001
#define AVR32_INTC_IRR11_IREQUEST352_OFFSET                          0
#define AVR32_INTC_IRR11_IREQUEST352_SIZE                            1
#define AVR32_INTC_IRR11_MASK                               0x00000001
#define AVR32_INTC_IRR11_RESETVALUE                         0x00000000
#define AVR32_INTC_IRR12                                    0x00000130
#define AVR32_INTC_IRR12_IREQUEST384                                 0
#define AVR32_INTC_IRR12_IREQUEST384_MASK                   0x00000001
#define AVR32_INTC_IRR12_IREQUEST384_OFFSET                          0
#define AVR32_INTC_IRR12_IREQUEST384_SIZE                            1
#define AVR32_INTC_IRR12_MASK                               0x00000001
#define AVR32_INTC_IRR12_RESETVALUE                         0x00000000
#define AVR32_INTC_IRR13                                    0x00000134
#define AVR32_INTC_IRR13_IREQUEST416                                 0
#define AVR32_INTC_IRR13_IREQUEST416_MASK                   0x00000001
#define AVR32_INTC_IRR13_IREQUEST416_OFFSET                          0
#define AVR32_INTC_IRR13_IREQUEST416_SIZE                            1
#define AVR32_INTC_IRR13_MASK                               0x00000001
#define AVR32_INTC_IRR13_RESETVALUE                         0x00000000
#define AVR32_INTC_IRR14                                    0x00000138
#define AVR32_INTC_IRR14_IREQUEST448                                 0
#define AVR32_INTC_IRR14_IREQUEST448_MASK                   0x00000001
#define AVR32_INTC_IRR14_IREQUEST448_OFFSET                          0
#define AVR32_INTC_IRR14_IREQUEST448_SIZE                            1
#define AVR32_INTC_IRR14_IREQUEST449                                 1
#define AVR32_INTC_IRR14_IREQUEST449_MASK                   0x00000002
#define AVR32_INTC_IRR14_IREQUEST449_OFFSET                          1
#define AVR32_INTC_IRR14_IREQUEST449_SIZE                            1
#define AVR32_INTC_IRR14_IREQUEST450                                 2
#define AVR32_INTC_IRR14_IREQUEST450_MASK                   0x00000004
#define AVR32_INTC_IRR14_IREQUEST450_OFFSET                          2
#define AVR32_INTC_IRR14_IREQUEST450_SIZE                            1
#define AVR32_INTC_IRR14_MASK                               0x00000007
#define AVR32_INTC_IRR14_RESETVALUE                         0x00000000
#define AVR32_INTC_IRR15                                    0x0000013c
#define AVR32_INTC_IRR15_IREQUEST480                                 0
#define AVR32_INTC_IRR15_IREQUEST480_MASK                   0x00000001
#define AVR32_INTC_IRR15_IREQUEST480_OFFSET                          0
#define AVR32_INTC_IRR15_IREQUEST480_SIZE                            1
#define AVR32_INTC_IRR15_MASK                               0x00000001
#define AVR32_INTC_IRR15_RESETVALUE                         0x00000000
#define AVR32_INTC_IRR16                                    0x00000140
#define AVR32_INTC_IRR16_IREQUEST512                                 0
#define AVR32_INTC_IRR16_IREQUEST512_MASK                   0x00000001
#define AVR32_INTC_IRR16_IREQUEST512_OFFSET                          0
#define AVR32_INTC_IRR16_IREQUEST512_SIZE                            1
#define AVR32_INTC_IRR16_MASK                               0x00000001
#define AVR32_INTC_IRR16_RESETVALUE                         0x00000000
#define AVR32_INTC_IRR17                                    0x00000144
#define AVR32_INTC_IRR17_IREQUEST544                                 0
#define AVR32_INTC_IRR17_IREQUEST544_MASK                   0x00000001
#define AVR32_INTC_IRR17_IREQUEST544_OFFSET                          0
#define AVR32_INTC_IRR17_IREQUEST544_SIZE                            1
#define AVR32_INTC_IRR17_MASK                               0x00000001
#define AVR32_INTC_IRR17_RESETVALUE                         0x00000000
#define AVR32_INTC_IRR18                                    0x00000148
#define AVR32_INTC_IRR18_IREQUEST576                                 0
#define AVR32_INTC_IRR18_IREQUEST576_MASK                   0x00000001
#define AVR32_INTC_IRR18_IREQUEST576_OFFSET                          0
#define AVR32_INTC_IRR18_IREQUEST576_SIZE                            1
#define AVR32_INTC_IRR18_MASK                               0x00000001
#define AVR32_INTC_IRR18_RESETVALUE                         0x00000000
#define AVR32_INTC_IRR19                                    0x0000014c
#define AVR32_INTC_IRR19_IREQUEST608                                 0
#define AVR32_INTC_IRR19_IREQUEST608_MASK                   0x00000001
#define AVR32_INTC_IRR19_IREQUEST608_OFFSET                          0
#define AVR32_INTC_IRR19_IREQUEST608_SIZE                            1
#define AVR32_INTC_IRR19_MASK                               0x00000001
#define AVR32_INTC_IRR19_RESETVALUE                         0x00000000
#define AVR32_INTC_IRR1_IREQUEST32                                   0
#define AVR32_INTC_IRR1_IREQUEST32_MASK                     0x00000001
#define AVR32_INTC_IRR1_IREQUEST32_OFFSET                            0
#define AVR32_INTC_IRR1_IREQUEST32_SIZE                              1
#define AVR32_INTC_IRR1_IREQUEST33                                   1
#define AVR32_INTC_IRR1_IREQUEST33_MASK                     0x00000002
#define AVR32_INTC_IRR1_IREQUEST33_OFFSET                            1
#define AVR32_INTC_IRR1_IREQUEST33_SIZE                              1
#define AVR32_INTC_IRR1_IREQUEST34                                   2
#define AVR32_INTC_IRR1_IREQUEST34_MASK                     0x00000004
#define AVR32_INTC_IRR1_IREQUEST34_OFFSET                            2
#define AVR32_INTC_IRR1_IREQUEST34_SIZE                              1
#define AVR32_INTC_IRR1_IREQUEST35                                   3
#define AVR32_INTC_IRR1_IREQUEST35_MASK                     0x00000008
#define AVR32_INTC_IRR1_IREQUEST35_OFFSET                            3
#define AVR32_INTC_IRR1_IREQUEST35_SIZE                              1
#define AVR32_INTC_IRR1_IREQUEST36                                   4
#define AVR32_INTC_IRR1_IREQUEST36_MASK                     0x00000010
#define AVR32_INTC_IRR1_IREQUEST36_OFFSET                            4
#define AVR32_INTC_IRR1_IREQUEST36_SIZE                              1
#define AVR32_INTC_IRR1_IREQUEST37                                   5
#define AVR32_INTC_IRR1_IREQUEST37_MASK                     0x00000020
#define AVR32_INTC_IRR1_IREQUEST37_OFFSET                            5
#define AVR32_INTC_IRR1_IREQUEST37_SIZE                              1
#define AVR32_INTC_IRR1_IREQUEST38                                   6
#define AVR32_INTC_IRR1_IREQUEST38_MASK                     0x00000040
#define AVR32_INTC_IRR1_IREQUEST38_OFFSET                            6
#define AVR32_INTC_IRR1_IREQUEST38_SIZE                              1
#define AVR32_INTC_IRR1_IREQUEST39                                   7
#define AVR32_INTC_IRR1_IREQUEST39_MASK                     0x00000080
#define AVR32_INTC_IRR1_IREQUEST39_OFFSET                            7
#define AVR32_INTC_IRR1_IREQUEST39_SIZE                              1
#define AVR32_INTC_IRR1_IREQUEST40                                   8
#define AVR32_INTC_IRR1_IREQUEST40_MASK                     0x00000100
#define AVR32_INTC_IRR1_IREQUEST40_OFFSET                            8
#define AVR32_INTC_IRR1_IREQUEST40_SIZE                              1
#define AVR32_INTC_IRR1_IREQUEST41                                   9
#define AVR32_INTC_IRR1_IREQUEST41_MASK                     0x00000200
#define AVR32_INTC_IRR1_IREQUEST41_OFFSET                            9
#define AVR32_INTC_IRR1_IREQUEST41_SIZE                              1
#define AVR32_INTC_IRR1_IREQUEST42                                  10
#define AVR32_INTC_IRR1_IREQUEST42_MASK                     0x00000400
#define AVR32_INTC_IRR1_IREQUEST42_OFFSET                           10
#define AVR32_INTC_IRR1_IREQUEST42_SIZE                              1
#define AVR32_INTC_IRR1_MASK                                0x000007ff
#define AVR32_INTC_IRR1_RESETVALUE                          0x00000000
#define AVR32_INTC_IRR2                                     0x00000108
#define AVR32_INTC_IRR2_IREQUEST64                                   0
#define AVR32_INTC_IRR2_IREQUEST64_MASK                     0x00000001
#define AVR32_INTC_IRR2_IREQUEST64_OFFSET                            0
#define AVR32_INTC_IRR2_IREQUEST64_SIZE                              1
#define AVR32_INTC_IRR2_IREQUEST65                                   1
#define AVR32_INTC_IRR2_IREQUEST65_MASK                     0x00000002
#define AVR32_INTC_IRR2_IREQUEST65_OFFSET                            1
#define AVR32_INTC_IRR2_IREQUEST65_SIZE                              1
#define AVR32_INTC_IRR2_IREQUEST66                                   2
#define AVR32_INTC_IRR2_IREQUEST66_MASK                     0x00000004
#define AVR32_INTC_IRR2_IREQUEST66_OFFSET                            2
#define AVR32_INTC_IRR2_IREQUEST66_SIZE                              1
#define AVR32_INTC_IRR2_IREQUEST67                                   3
#define AVR32_INTC_IRR2_IREQUEST67_MASK                     0x00000008
#define AVR32_INTC_IRR2_IREQUEST67_OFFSET                            3
#define AVR32_INTC_IRR2_IREQUEST67_SIZE                              1
#define AVR32_INTC_IRR2_IREQUEST68                                   4
#define AVR32_INTC_IRR2_IREQUEST68_MASK                     0x00000010
#define AVR32_INTC_IRR2_IREQUEST68_OFFSET                            4
#define AVR32_INTC_IRR2_IREQUEST68_SIZE                              1
#define AVR32_INTC_IRR2_IREQUEST69                                   5
#define AVR32_INTC_IRR2_IREQUEST69_MASK                     0x00000020
#define AVR32_INTC_IRR2_IREQUEST69_OFFSET                            5
#define AVR32_INTC_IRR2_IREQUEST69_SIZE                              1
#define AVR32_INTC_IRR2_IREQUEST70                                   6
#define AVR32_INTC_IRR2_IREQUEST70_MASK                     0x00000040
#define AVR32_INTC_IRR2_IREQUEST70_OFFSET                            6
#define AVR32_INTC_IRR2_IREQUEST70_SIZE                              1
#define AVR32_INTC_IRR2_IREQUEST71                                   7
#define AVR32_INTC_IRR2_IREQUEST71_MASK                     0x00000080
#define AVR32_INTC_IRR2_IREQUEST71_OFFSET                            7
#define AVR32_INTC_IRR2_IREQUEST71_SIZE                              1
#define AVR32_INTC_IRR2_IREQUEST72                                   8
#define AVR32_INTC_IRR2_IREQUEST72_MASK                     0x00000100
#define AVR32_INTC_IRR2_IREQUEST72_OFFSET                            8
#define AVR32_INTC_IRR2_IREQUEST72_SIZE                              1
#define AVR32_INTC_IRR2_IREQUEST73                                   9
#define AVR32_INTC_IRR2_IREQUEST73_MASK                     0x00000200
#define AVR32_INTC_IRR2_IREQUEST73_OFFSET                            9
#define AVR32_INTC_IRR2_IREQUEST73_SIZE                              1
#define AVR32_INTC_IRR2_IREQUEST74                                  10
#define AVR32_INTC_IRR2_IREQUEST74_MASK                     0x00000400
#define AVR32_INTC_IRR2_IREQUEST74_OFFSET                           10
#define AVR32_INTC_IRR2_IREQUEST74_SIZE                              1
#define AVR32_INTC_IRR2_IREQUEST75                                  11
#define AVR32_INTC_IRR2_IREQUEST75_MASK                     0x00000800
#define AVR32_INTC_IRR2_IREQUEST75_OFFSET                           11
#define AVR32_INTC_IRR2_IREQUEST75_SIZE                              1
#define AVR32_INTC_IRR2_IREQUEST76                                  12
#define AVR32_INTC_IRR2_IREQUEST76_MASK                     0x00001000
#define AVR32_INTC_IRR2_IREQUEST76_OFFSET                           12
#define AVR32_INTC_IRR2_IREQUEST76_SIZE                              1
#define AVR32_INTC_IRR2_IREQUEST77                                  13
#define AVR32_INTC_IRR2_IREQUEST77_MASK                     0x00002000
#define AVR32_INTC_IRR2_IREQUEST77_OFFSET                           13
#define AVR32_INTC_IRR2_IREQUEST77_SIZE                              1
#define AVR32_INTC_IRR2_MASK                                0x00003fff
#define AVR32_INTC_IRR2_RESETVALUE                          0x00000000
#define AVR32_INTC_IRR3                                     0x0000010c
#define AVR32_INTC_IRR3_IREQUEST100                                  4
#define AVR32_INTC_IRR3_IREQUEST100_MASK                    0x00000010
#define AVR32_INTC_IRR3_IREQUEST100_OFFSET                           4
#define AVR32_INTC_IRR3_IREQUEST100_SIZE                             1
#define AVR32_INTC_IRR3_IREQUEST101                                  5
#define AVR32_INTC_IRR3_IREQUEST101_MASK                    0x00000020
#define AVR32_INTC_IRR3_IREQUEST101_OFFSET                           5
#define AVR32_INTC_IRR3_IREQUEST101_SIZE                             1
#define AVR32_INTC_IRR3_IREQUEST102                                  6
#define AVR32_INTC_IRR3_IREQUEST102_MASK                    0x00000040
#define AVR32_INTC_IRR3_IREQUEST102_OFFSET                           6
#define AVR32_INTC_IRR3_IREQUEST102_SIZE                             1
#define AVR32_INTC_IRR3_IREQUEST103                                  7
#define AVR32_INTC_IRR3_IREQUEST103_MASK                    0x00000080
#define AVR32_INTC_IRR3_IREQUEST103_OFFSET                           7
#define AVR32_INTC_IRR3_IREQUEST103_SIZE                             1
#define AVR32_INTC_IRR3_IREQUEST104                                  8
#define AVR32_INTC_IRR3_IREQUEST104_MASK                    0x00000100
#define AVR32_INTC_IRR3_IREQUEST104_OFFSET                           8
#define AVR32_INTC_IRR3_IREQUEST104_SIZE                             1
#define AVR32_INTC_IRR3_IREQUEST105                                  9
#define AVR32_INTC_IRR3_IREQUEST105_MASK                    0x00000200
#define AVR32_INTC_IRR3_IREQUEST105_OFFSET                           9
#define AVR32_INTC_IRR3_IREQUEST105_SIZE                             1
#define AVR32_INTC_IRR3_IREQUEST106                                 10
#define AVR32_INTC_IRR3_IREQUEST106_MASK                    0x00000400
#define AVR32_INTC_IRR3_IREQUEST106_OFFSET                          10
#define AVR32_INTC_IRR3_IREQUEST106_SIZE                             1
#define AVR32_INTC_IRR3_IREQUEST107                                 11
#define AVR32_INTC_IRR3_IREQUEST107_MASK                    0x00000800
#define AVR32_INTC_IRR3_IREQUEST107_OFFSET                          11
#define AVR32_INTC_IRR3_IREQUEST107_SIZE                             1
#define AVR32_INTC_IRR3_IREQUEST108                                 12
#define AVR32_INTC_IRR3_IREQUEST108_MASK                    0x00001000
#define AVR32_INTC_IRR3_IREQUEST108_OFFSET                          12
#define AVR32_INTC_IRR3_IREQUEST108_SIZE                             1
#define AVR32_INTC_IRR3_IREQUEST109                                 13
#define AVR32_INTC_IRR3_IREQUEST109_MASK                    0x00002000
#define AVR32_INTC_IRR3_IREQUEST109_OFFSET                          13
#define AVR32_INTC_IRR3_IREQUEST109_SIZE                             1
#define AVR32_INTC_IRR3_IREQUEST110                                 14
#define AVR32_INTC_IRR3_IREQUEST110_MASK                    0x00004000
#define AVR32_INTC_IRR3_IREQUEST110_OFFSET                          14
#define AVR32_INTC_IRR3_IREQUEST110_SIZE                             1
#define AVR32_INTC_IRR3_IREQUEST96                                   0
#define AVR32_INTC_IRR3_IREQUEST96_MASK                     0x00000001
#define AVR32_INTC_IRR3_IREQUEST96_OFFSET                            0
#define AVR32_INTC_IRR3_IREQUEST96_SIZE                              1
#define AVR32_INTC_IRR3_IREQUEST97                                   1
#define AVR32_INTC_IRR3_IREQUEST97_MASK                     0x00000002
#define AVR32_INTC_IRR3_IREQUEST97_OFFSET                            1
#define AVR32_INTC_IRR3_IREQUEST97_SIZE                              1
#define AVR32_INTC_IRR3_IREQUEST98                                   2
#define AVR32_INTC_IRR3_IREQUEST98_MASK                     0x00000004
#define AVR32_INTC_IRR3_IREQUEST98_OFFSET                            2
#define AVR32_INTC_IRR3_IREQUEST98_SIZE                              1
#define AVR32_INTC_IRR3_IREQUEST99                                   3
#define AVR32_INTC_IRR3_IREQUEST99_MASK                     0x00000008
#define AVR32_INTC_IRR3_IREQUEST99_OFFSET                            3
#define AVR32_INTC_IRR3_IREQUEST99_SIZE                              1
#define AVR32_INTC_IRR3_MASK                                0x00007fff
#define AVR32_INTC_IRR3_RESETVALUE                          0x00000000
#define AVR32_INTC_IRR4                                     0x00000110
#define AVR32_INTC_IRR4_IREQUEST128                                  0
#define AVR32_INTC_IRR4_IREQUEST128_MASK                    0x00000001
#define AVR32_INTC_IRR4_IREQUEST128_OFFSET                           0
#define AVR32_INTC_IRR4_IREQUEST128_SIZE                             1
#define AVR32_INTC_IRR4_MASK                                0x00000001
#define AVR32_INTC_IRR4_RESETVALUE                          0x00000000
#define AVR32_INTC_IRR5                                     0x00000114
#define AVR32_INTC_IRR5_IREQUEST160                                  0
#define AVR32_INTC_IRR5_IREQUEST160_MASK                    0x00000001
#define AVR32_INTC_IRR5_IREQUEST160_OFFSET                           0
#define AVR32_INTC_IRR5_IREQUEST160_SIZE                             1
#define AVR32_INTC_IRR5_MASK                                0x00000001
#define AVR32_INTC_IRR5_RESETVALUE                          0x00000000
#define AVR32_INTC_IRR6                                     0x00000118
#define AVR32_INTC_IRR6_IREQUEST192                                  0
#define AVR32_INTC_IRR6_IREQUEST192_MASK                    0x00000001
#define AVR32_INTC_IRR6_IREQUEST192_OFFSET                           0
#define AVR32_INTC_IRR6_IREQUEST192_SIZE                             1
#define AVR32_INTC_IRR6_MASK                                0x00000001
#define AVR32_INTC_IRR6_RESETVALUE                          0x00000000
#define AVR32_INTC_IRR7                                     0x0000011c
#define AVR32_INTC_IRR7_IREQUEST224                                  0
#define AVR32_INTC_IRR7_IREQUEST224_MASK                    0x00000001
#define AVR32_INTC_IRR7_IREQUEST224_OFFSET                           0
#define AVR32_INTC_IRR7_IREQUEST224_SIZE                             1
#define AVR32_INTC_IRR7_MASK                                0x00000001
#define AVR32_INTC_IRR7_RESETVALUE                          0x00000000
#define AVR32_INTC_IRR8                                     0x00000120
#define AVR32_INTC_IRR8_IREQUEST256                                  0
#define AVR32_INTC_IRR8_IREQUEST256_MASK                    0x00000001
#define AVR32_INTC_IRR8_IREQUEST256_OFFSET                           0
#define AVR32_INTC_IRR8_IREQUEST256_SIZE                             1
#define AVR32_INTC_IRR8_MASK                                0x00000001
#define AVR32_INTC_IRR8_RESETVALUE                          0x00000000
#define AVR32_INTC_IRR9                                     0x00000124
#define AVR32_INTC_IRR9_IREQUEST288                                  0
#define AVR32_INTC_IRR9_IREQUEST288_MASK                    0x00000001
#define AVR32_INTC_IRR9_IREQUEST288_OFFSET                           0
#define AVR32_INTC_IRR9_IREQUEST288_SIZE                             1
#define AVR32_INTC_IRR9_MASK                                0x00000001
#define AVR32_INTC_IRR9_RESETVALUE                          0x00000000


#ifdef __AVR32_ABI_COMPILER__

typedef struct avr32_intc_t {
  /*0x000*/
        unsigned long ipr[64];
  /*0x100*/
  const unsigned long irr[64];
  /*0x200*/
  const unsigned long icr3;
  const unsigned long icr2;
  const unsigned long icr1;
  const unsigned long icr0;
} avr32_intc_t;


/* #ifdef __AVR32_ABI_COMPILER__ */
#endif

/*#ifdef AVR32_UC3A1512_INTC_H_INCLUDED*/
#endif

