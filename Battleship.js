/* This solution is made to simulate Battleship game
 * Given the ship locations and hits in the game, returns the number of
 * sunken ships and number of hit ships [1, 1]
 * @param N the size of the board game
 * @param S array with the location of the Ships (e.g., [1A, 2B])
 * @param S array with the hits 
*/

function solution(N, S, T) {
  let shipArr = S.split(',');

	var hitShips = 0;
	var sunkShips = 0;
	let hitArr = T.split(',');

	shipArr.forEach(ship => {
		var hitCount = 0;
		hitArr.forEach(hit => {
			if(isShipHit(ship, hit)){
				hitCount++;
		    }
	    });
		if(hitCount !== 0){
		    if(hitCount === getShipSize(ship)){
		        sunkShips++;
		    } else {
		        hitShips++;
		    }
		}
	});

	// count and return
	return `${sunkShips},${hitShips}`;
}

function isShipHit(ship, hit){
	var isHit = false;
	var topLeft = ship.split(' ')[0];
	var bottomRight = ship.split(' ')[1];
	let hitRow = getRow(hit);
	let hitCol = getCol(hit);
	if((hitRow >= getRow(topLeft) && hitRow <= getRow(bottomRight)) &&
        (hitCol >= getCol(topLeft) && hitCol <= getCol(bottomRight))){
        return true;
    } else {
        return false;
    }
}

function getRow(pos){
    if(pos.length === 2){
        return pos.charAt(0);
    } else {
        return pos.charAt(0) + pos.charAt(1);
    }
}

function getCol(pos){
    if(pos.length === 2){
        return pos.charCodeAt(1);
    } else {
        return pos.charCodeAt(2);
    }
}

function getShipSize(ship){
    var topLeft = ship.split(' ')[0];
	var bottomRight = ship.split(' ')[1];
    var width = getCol(bottomRight) - getCol(topLeft) + 1;
    var height = getRow(bottomRight) - getRow(topLeft) + 1;
    return width * height;
}
