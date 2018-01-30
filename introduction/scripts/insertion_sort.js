var canvas = document.getElementById("canvas0");
if (canvas) {
	canvas.width = "1000";
	canvas.height = "5000";
	pen = canvas.getContext("2d");
	var nums = [];
	for (var i = 0; i < 10; i++)
		nums[i] = Math.floor(Math.random() * 100);
	drawArray(pen, nums, 10, 10);
	alert("hello");
	insertion_sort(nums);
}

function insertion_sort(array) {
	for (var i = 0, line = 100; i < array.length; i++) {
		drawArray(pen, nums, 10, line, i);
		line += 90;
		for (var j = i + 1; j > 0; j--, line += 90) {
			if (array[j] < array[ j - 1]) {
				var temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;
			} else {
				break;
			}
			drawArray(pen, nums, 10, line, j - 1, j);
		}
	}
}