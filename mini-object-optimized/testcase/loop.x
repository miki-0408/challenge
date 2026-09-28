
# tac list

0x560a4be7cee0	label main
0x560a4be7cf20	begin
0x560a4be7a800	var a
0x560a4be7a8a0	var b
0x560a4be7a940	var c
0x560a4be7ab20	var i
0x560a4be7abc0	var j
0x560a4be7acc0	input a
0x560a4be7ad20	input b
0x560a4be7ad80	input c
0x560a4be7ae90	j = 5
0x560a4be7f100	label L8
0x560a4be7f1a0	var t28
0x560a4be7f1e0	t28 = b * c
0x560a4be7f280	var t29
0x560a4be7f2c0	t29 = a + t28
0x560a4be7f360	var t30
0x560a4be7f3a0	t30 = a + c
0x560a4be7f440	var t31
0x560a4be7f480	t31 = t30 / b
0x560a4be7f520	var t32
0x560a4be7f560	t32 = t29 - t31
0x560a4be7f600	var t33
0x560a4be7f640	t33 = t32 + 9
0x560a4be7f800	var t35
0x560a4be7f840	t35 = a + t28
0x560a4be7f8e0	var t36
0x560a4be7f920	t36 = c - a
0x560a4be7f9c0	var t37
0x560a4be7fa00	t37 = t36 / b
0x560a4be7faa0	var t38
0x560a4be7fae0	t38 = t35 - t37
0x560a4be7fb80	var t39
0x560a4be7fbc0	t39 = t38 + 9
0x560a4be7cae0	label L4
0x560a4be7b030	var t0
0x560a4be7b070	t0 = (j > 0)
0x560a4be7cc20	ifz t0 goto L5
0x560a4be7b0d0	output j
0x560a4be7b1e0	i = 9
0x560a4be7dc40	label L7
0x560a4be7c660	label L1
0x560a4be7b320	var t1
0x560a4be7b360	t1 = (i > 0)
0x560a4be7c7a0	ifz t1 goto L2
0x560a4be7b3c0	output i
0x560a4be7c520	var t14
0x560a4be7c560	t14 = i - 1
0x560a4be7c5a0	i = t14
0x560a4be7c6a0	goto L1
0x560a4be7c760	label L2
0x560a4be7c900	var t15
0x560a4be7c940	t15 = j - 1
0x560a4be7c980	j = t15
0x560a4be7ca20	output L3
0x560a4be7cb20	goto L4
0x560a4be7cbe0	label L5
0x560a4be7ccc0	output L6
0x560a4be7cd20	output t33
0x560a4be7cd80	output L3
0x560a4be7cde0	output t39
0x560a4be7ce40	output L6
0x560a4be7cf60	end
