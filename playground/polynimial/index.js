const Complex = require('complex.js')

//https://en.m.wikipedia.org/wiki/Durand%E2%80%93Kerner_method
// (x-2)(x+5)^2(x+3)^2
// x^5+14x^4+62x^3+52x^2-255x-450
console.time('time')

const aArr = [
	new Complex(-1, 0),
	new Complex(0, 0),
	new Complex(0, 0),
	new Complex(1, 0),
	// new Complex(-450, 0),
	// new Complex(-255, 0),
	// new Complex(52, 0),
	// new Complex(62, 0),
	// new Complex(14, 0),
	// new Complex(1, 0),
]

const n = aArr.length - 1
const radius = Math.pow(aArr[0].div(aArr[n]).abs(), 1/n)

const round = (z, dec = 0) => !dec ? z : new Complex(Math.round(z.re*10**dec)/10**dec, Math.round(z.im*10**dec)/10**dec)
const arrRound = (arr, dec = 0) => !dec ? arr : arr.map(x => round(x, dec))

let xArr = Array(n).fill(0).map((_, i) => new Complex({r: radius, phi: i*2*Math.PI/n + Math.PI/2}))

console.log('aArr', arrRound(aArr))

const IT_MAX = 1e6
const DELTA_MIN = 1e-6

let i
for (i = 0; i < IT_MAX; i++) {
	// console.log('---------- xArr: ', i, '\n', arrRound(xArr))
	nextXArr = []
	let delta = 0
	for (let j = 0; j < xArr.length; j++) {
		const currX = xArr[j]
		const top = aArr.reduce((acc, _, n) => acc.add( aArr[n].mul(currX.pow(n)) ), new Complex(0, 0))
		const bottom = xArr.reduce((acc, _, n) => acc.mul( n == j ? 1 : currX.sub(xArr[n]) ), new Complex(1, 0))
		const nextX = currX.sub(top.div(bottom))
		nextXArr.push(nextX)
		delta = Math.max(delta, Math.abs(nextX.im - currX.im), Math.abs(nextX.re - currX.re))
	}
	console.log(delta)
	xArr = nextXArr
	if (delta < DELTA_MIN) break
}

console.log('---------- xArr: ', i, '\n', arrRound(xArr))
console.log('---------- xArr: ', i, '\n', arrRound(xArr, 5))

console.timeEnd('time')