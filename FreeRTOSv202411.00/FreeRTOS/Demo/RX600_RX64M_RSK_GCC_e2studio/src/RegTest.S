;/*
; * FreeRTOS V202411.00
; * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
; *
; * Permission is hereby granted, free of charge, to any person obtaining a copy of
; * this software and associated documentation files (the "Software"), to deal in
; * the Software without restriction, including without limitation the rights to
; * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
; * the Software, and to permit persons to whom the Software is furnished to do so,
; * subject to the following conditions:
; *
; * The above copyright notice and this permission notice shall be included in all
; * copies or substantial portions of the Software.
; *
; * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
; * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
; * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
; * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
; *
; * https://www.FreeRTOS.org
; * https://github.com/FreeRTOS
; *
; * 1 tab == 4 spaces!
; */

	.global _vRegTest1Implementation
	.global _vRegTest2Implementation

	.extern _ulRegTest1LoopCounter
	.extern _ulRegTest2LoopCounter

	.text


;/* This function is explained in the comments at the top of main.c. */
_vRegTest1Implementation:

	;/* Put a known value in the guard byte of the accumulators. */
	MOV.L	#10, R1
	MVTACGU R1, A0
	MOV.L	#20, R1
	MVTACGU R1, A1

	;/* Put a known value in each register. */
	MOV.L	#1, R1
	MOV.L	#2, R2
	MOV.L	#3, R3
	MOV.L	#4, R4
	MOV.L	#5, R5
	MOV.L	#6, R6
	MOV.L	#7, R7
	MOV.L	#8, R8
	MOV.L	#9, R9
	MOV.L	#10, R10
	MOV.L	#11, R11
	MOV.L	#12, R12
	MOV.L	#13, R13
	MOV.L	#14, R14
	MOV.L	#15, R15

	;/* Put a known value in the hi and low of the accumulators. */
	MVTACHI R1, A0
	MVTACLO R2, A0
	MVTACHI R3, A1
	MVTACLO R4, A1

	;/* Loop, checking each iteration that each register still contains the
	;expected value. */
TestLoop1:

	;/* Push the registers that are going to get clobbered. */
	PUSHM	R14-R15

	;/* Increment the loop counter to show this task is still getting CPU time. */
	MOV.L	#_ulRegTest1LoopCounter, R14
	MOV.L	[ R14 ], R15
	ADD	#1, R15
	MOV.L	R15, [ R14 ]

	;/* Yield to extend the text coverage.  Set the bit in the ITU SWINTR register. */
	MOV.L	#1, R14
	MOV.L 	#0872E0H, R15
	MOV.B	R14, [R15]
	NOP
	NOP

	;/* Check accumulators. */
	MVFACHI	#0, A0, R15
	CMP #1, R15
	BNE RegTest1Error
	MVFACLO	#0, A0, R15
	CMP #2, R15
	BNE RegTest1Error
	MVFACGU	#0, A0, R15
	CMP #10, R15
	BNE RegTest1Error
	MVFACHI	#0, A1, R15
	CMP #3, R15
	BNE RegTest1Error
	MVFACLO	#0, A1, R15
	CMP #4, R15
	BNE RegTest1Error
	MVFACGU	#0, A1, R15
	CMP #20, R15
	BNE RegTest1Error

	;/* Restore the clobbered registers. */
	POPM	R14-R15

	;/* Now compare each register to ensure it still contains the value that was
	;set before this loop was entered. */
	CMP	#1, R1
	BNE	RegTest1Error
	CMP	#2, R2
	BNE	RegTest1Error
	CMP	#3, R3
	BNE	RegTest1Error
	CMP	#4, R4
	BNE	RegTest1Error
	CMP	#5, R5
	BNE	RegTest1Error
	CMP	#6, R6
	BNE	RegTest1Error
	CMP	#7, R7
	BNE	RegTest1Error
	CMP	#8, R8
	BNE	RegTest1Error
	CMP	#9, R9
	BNE	RegTest1Error
	CMP	#10, R10
	BNE	RegTest1Error
	CMP	#11, R11
	BNE	RegTest1Error
	CMP	#12, R12
	BNE	RegTest1Error
	CMP	#13, R13
	BNE	RegTest1Error
	CMP	#14, R14
	BNE	RegTest1Error
	CMP	#15, R15
	BNE	RegTest1Error

	;/* All comparisons passed, start a new itteratio of this loop. */
	BRA		TestLoop1

RegTest1Error:
	;/* A compare failed, just loop here so the loop counter stops incrementing
	;- causing the check task to indicate the error. */
	BRA RegTest1Error
;/*-----------------------------------------------------------*/

;/* This function is explained in the comments at the top of main.c. */
_vRegTest2Implementation:

	;/* Put a known value in the guard byte of the accumulators. */
	MOV.L	#1H, R1
	MVTACGU R1, A0
	MOV.L	#2H, R1
	MVTACGU R1, A1

	;/* Put a known value in each general purpose register. */
	MOV.L	#10H, R1
	MOV.L	#20H, R2
	MOV.L	#30H, R3
	MOV.L	#40H, R4
	MOV.L	#50H, R5
	MOV.L	#60H, R6
	MOV.L	#70H, R7
	MOV.L	#80H, R8
	MOV.L	#90H, R9
	MOV.L	#100H, R10
	MOV.L	#110H, R11
	MOV.L	#120H, R12
	MOV.L	#130H, R13
	MOV.L	#140H, R14
	MOV.L	#150H, R15

	;/* Put a known value in the hi and low of the accumulators. */
	MVTACHI R1, A0
	MVTACLO R2, A0
	MVTACHI R3, A1
	MVTACLO R4, A1

	;/* Loop, checking each iteration that each register still contains the
	;expected value. */
TestLoop2:

	;/* Push the registers that are going to get clobbered. */
	PUSHM	R14-R15

	;/* Increment the loop counter to show this task is still getting CPU time. */
	MOV.L	#_ulRegTest2LoopCounter, R14
	MOV.L	[ R14 ], R15
	ADD	#1, R15
	MOV.L	R15, [ R14 ]

	;/* Check accumulators. */
	MVFACHI	#0, A0, R15
	CMP #10H, R15
	BNE RegTest1Error
	MVFACLO	#0, A0, R15
	CMP #20H, R15
	BNE RegTest1Error
	MVFACGU	#0, A0, R15
	CMP #1H, R15
	BNE RegTest1Error
	MVFACHI	#0, A1, R15
	CMP #30H, R15
	BNE RegTest1Error
	MVFACLO	#0, A1, R15
	CMP #40H, R15
	BNE RegTest1Error
	MVFACGU	#0, A1, R15
	CMP #2H, R15
	BNE RegTest1Error

	;/* Restore the clobbered registers. */
	POPM	R14-R15

	;/* Now compare each register to ensure it still contains the value that was
	;set before this loop was entered. */
	CMP	#10H, R1
	BNE	RegTest2Error
	CMP	#20H, R2
	BNE	RegTest2Error
	CMP	#30H, R3
	BNE	RegTest2Error
	CMP	#40H, R4
	BNE	RegTest2Error
	CMP	#50H, R5
	BNE	RegTest2Error
	CMP	#60H, R6
	BNE	RegTest2Error
	CMP	#70H, R7
	BNE	RegTest2Error
	CMP	#80H, R8
	BNE	RegTest2Error
	CMP	#90H, R9
	BNE	RegTest2Error
	CMP	#100H, R10
	BNE	RegTest2Error
	CMP	#110H, R11
	BNE	RegTest2Error
	CMP	#120H, R12
	BNE	RegTest2Error
	CMP	#130H, R13
	BNE	RegTest2Error
	CMP	#140H, R14
	BNE	RegTest2Error
	CMP	#150H, R15
	BNE	RegTest2Error

	;/* All comparisons passed, start a new itteratio of this loop. */
	BRA	TestLoop2

RegTest2Error:
	;/* A compare failed, just loop here so the loop counter stops incrementing
	;- causing the check task to indicate the error. */
	BRA RegTest2Error


	.END
