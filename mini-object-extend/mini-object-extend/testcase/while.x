
# tac list

0x55d5e9bcd350	label main
0x55d5e9bcd390	begin
0x55d5e9bcc830	var i
0x55d5e9bcc900	var j
0x55d5e9bcca40	i = 0
0x55d5e9bccaa0	input j
0x55d5e9bcd0f0	label L1
0x55d5e9bccc10	var t0
0x55d5e9bccc50	t0 = (i < j)
0x55d5e9bcd130	ifz t0 goto L2
0x55d5e9bcccb0	output i
0x55d5e9bcced0	var t1
0x55d5e9bccf10	t1 = i + 1
0x55d5e9bccf50	i = t1
0x55d5e9bcd170	goto L1
0x55d5e9bcd1b0	label L2
0x55d5e9bcd280	output L3
0x55d5e9bcd3d0	end
