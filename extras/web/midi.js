// if (navigator.requestMIDIAccess) {
//     console.log('This browser supports WebMIDI!');
// } else {
//     console.log('WebMIDI is not supported in this browser.');
// }

// navigator.requestMIDIAccess()
//     .then(onMIDISuccess, onMIDIFailure);

// function onMIDISuccess(midiAccess) {
//     console.log(midiAccess);

//     var inputs = midiAccess.inputs;
//     var outputs = midiAccess.outputs;
// }

// function onMIDIFailure() {
//     console.log('Could not access your MIDI devices.');
// }




// function onMIDIMessage(event) {
// 	let str = `MIDI message received at timestamp ${event.timeStamp}[${event.data.length} bytes]: `;
// 	for (const character of event.data) {
// 	  str += `0x${character.toString(16)} `;
// 	}
// 	console.log(str);
//   }
  
//   function startLoggingMIDIInput(midiAccess, indexOfPort) {
// 	midiAccess.inputs.forEach((entry) => {entry.onmidimessage = onMIDIMessage;});
//   }

navigator.requestMIDIAccess().then((midiAccess) => {
	Array.from(midiAccess.inputs).forEach((input) => {
	  input[1].onmidimessage = (msg) => { console.log(msg); }
	})
  });
  

