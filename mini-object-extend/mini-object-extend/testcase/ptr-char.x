
# tac list

0x55d3763eeb00	label main
0x55d3763eeb40	begin
0x55d3763ed830	var a
0x55d3763ed900	var pa
0x55d3763ed9d0	var b
0x55d3763edaa0	var c
0x55d3763edb70	var d
0x55d3763edc40	var ptr
0x55d3763edca0	input d
0x55d3763eddc0	c = 99
0x55d3763edee0	b = 98
0x55d3763edf40	input a
0x55d3763ee220	ifz 0 goto L2
0x55d3763ee0f0	output L1
0x55d3763ee1e0	label L2
0x55d3763ee280	output a
0x55d3763ee2e0	output b
0x55d3763ee340	output c
0x55d3763ee3a0	output d
0x55d3763ee400	output L1
0x55d3763ee510	var t0
0x55d3763ee550	t0 = &a
0x55d3763ee5c0	pa = t0
0x55d3763ee710	*pa = 65
0x55d3763ee770	output a
0x55d3763ee820	ptr = pa
0x55d3763ee970	*ptr = 66
0x55d3763ee9d0	output a
0x55d3763eea30	output L1
0x55d3763eeb80	end
