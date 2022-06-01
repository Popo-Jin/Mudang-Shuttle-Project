const Stream = require('./node-rtsp-stream');

stream = new Stream({
  name: 'foscam_stream',
  streamUrl: 'rtsp://admin:pa$$word@192.168.0.xxx',
  wsPort: 11525, // 웹소켓을 통한 스트림 서비스 포트
  ffmpegOptions: { // options ffmpeg flags
    '-stats': '', // an option with no neccessary value uses a blank string
    '-force_fps': 30 // options with required values specify the value after the key, 30:blur있음
  }
});