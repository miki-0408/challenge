
# tac list

0x55bea3a0f430	label main
0x55bea3a0f470	begin
0x55bea3a0ca50	var i
0x55bea3a0cb20	var j
0x55bea3a0cbf0	var k
0x55bea3a0cce0	var zs
0x55bea3a0cd40	input i
0x55bea3a0cda0	input j
0x55bea3a0ce00	input k
0x55bea3a0cf90	var t0
0x55bea3a0cfd0	t0 = &zs
0x55bea3a0d0d0	var t1
0x55bea3a0d1a0	t1 = t0 + 0
0x55bea3a0d210	*t1 = i
0x55bea3a0d3a0	var t2
0x55bea3a0d3e0	t2 = &zs
0x55bea3a0d4e0	var t3
0x55bea3a0d5b0	t3 = t2 + 4
0x55bea3a0d620	*t3 = j
0x55bea3a0d7b0	var t4
0x55bea3a0d7f0	t4 = &zs
0x55bea3a0d8f0	var t5
0x55bea3a0d9c0	t5 = t4 + 8
0x55bea3a0da30	*t5 = k
0x55bea3a0dca0	ifz 0 goto L2
0x55bea3a0db50	output L1
0x55bea3a0dc60	label L2
0x55bea3a0dde0	var t6
0x55bea3a0de20	t6 = &zs
0x55bea3a0df20	var t7
0x55bea3a0df60	t7 = t6 + 8
0x55bea3a0e060	var t8
0x55bea3a0e0a0	t8 = *t7
0x55bea3a0e280	var t9
0x55bea3a0e2c0	t9 = t8 + 100
0x55bea3a0e300	i = t9
0x55bea3a0e460	var t10
0x55bea3a0e4a0	t10 = &zs
0x55bea3a0e5a0	var t11
0x55bea3a0e5e0	t11 = t10 + 4
0x55bea3a0e6e0	var t12
0x55bea3a0e720	t12 = *t11
0x55bea3a0e900	var t13
0x55bea3a0e940	t13 = t12 + 200
0x55bea3a0e980	j = t13
0x55bea3a0eae0	var t14
0x55bea3a0eb20	t14 = &zs
0x55bea3a0ec20	var t15
0x55bea3a0ec60	t15 = t14 + 0
0x55bea3a0ed60	var t16
0x55bea3a0eda0	t16 = *t15
0x55bea3a0ef80	var t17
0x55bea3a0efc0	t17 = t16 + 300
0x55bea3a0f000	k = t17
0x55bea3a0f1e0	ifz 0 goto L3
0x55bea3a0f0b0	output L1
0x55bea3a0f1a0	label L3
0x55bea3a0f240	output i
0x55bea3a0f2a0	output j
0x55bea3a0f300	output k
0x55bea3a0f360	output L1
0x55bea3a0f4b0	end
