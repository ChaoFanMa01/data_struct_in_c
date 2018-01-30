var canvas = document.getElementById("canvas0");
if (canvas) {
	canvas.width = "1000";
	canvas.height = "300";
	pen = canvas.getContext("2d");
	var nums = [];
	for (var i = 0; i < 10; i++)
		nums[i] = Math.floor(Math.random() * 100);
	drawArray(pen, nums, 10, 10, 4, 6);
//	drawBox(pen, 50, 50, 75, 55);
//	drawNum(pen, 20, 55, 95, "50px", "sans-serif");
//	drawBox(pen, 45, 55, 75, 55);
//	drawNum(pen, 20, 50, 100, "50px", "sans-serif");
}