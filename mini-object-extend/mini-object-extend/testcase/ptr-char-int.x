
# tac list

0x5572c7b4cb10	label main
0x5572c7b4cb50	begin
0x5572c7b4b830	var a
0x5572c7b4b900	var pa
0x5572c7b4b9d0	var b
0x5572c7b4baa0	var i
0x5572c7b4bb70	var pi
0x5572c7b4bc40	var j
0x5572c7b4bca0	input a
0x5572c7b4bd00	input i
0x5572c7b4c000	ifz 0 goto L2
0x5572c7b4beb0	output L1
0x5572c7b4bfc0	label L2
0x5572c7b4c0f0	var t0
0x5572c7b4c130	t0 = &a
0x5572c7b4c1a0	pa = t0
0x5572c7b4c2b0	var t1
0x5572c7b4c2f0	t1 = &i
0x5572c7b4c360	pi = t1
0x5572c7b4c4a0	var t2
0x5572c7b4c4e0	t2 = *pa
0x5572c7b4c550	b = t2
0x5572c7b4c690	var t3
0x5572c7b4c6d0	t3 = *pi
0x5572c7b4c740	j = t3
0x5572c7b4c920	ifz 0 goto L3
0x5572c7b4c7f0	output L1
0x5572c7b4c8e0	label L3
0x5572c7b4c980	output b
0x5572c7b4c9e0	output j
0x5572c7b4ca40	output L1
0x5572c7b4cb90	end
