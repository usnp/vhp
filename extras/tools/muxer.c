/* Copyright 2020 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mux/muxer.h"

#include <math.h>
#include <string.h>

#include "dsp/logging.h"
#include "dsp/math_constants.h"
#include "dsp/oscillator.h"

#define kLpfRadius 512
#define kLpfNumTaps (2 * kLfpRadius + 1)

/* Weaver LPF, a windowed FIR design by the Python code:
 *
 *   N = 8196
 *   f = np.arange(N//2 + 1) * Fs / N
 *   _, r = ss.sosfreqz(RECEIVER_WEAVER_LPF, f, fs=Fs)
 *   target_response = np.conj(r) / (np.abs(r)**2 + 0.001**2)
 *   target_response[f > WEAVER_LPF_CUTOFF_HZ] = 0.0
 *   weaver_lpf = np.fft.irfft(target_response, N)
 *   radius = 512
 *   weaver_lpf = np.append(weaver_lpf[-radius:], weaver_lpf[:radius + 1])
 *   weaver_lpf *= np.hamming(2 * radius + 1)
 *   weaver_lpf *= DIVISIONS * 2
 */
static const float kWeaverLpf[kLpfNumTaps] = {
    -5.634448e-3f, -5.693554e-3f, -5.738983e-3f, -5.770322e-3f, -5.787191e-3f,
    -5.789240e-3f, -5.776156e-3f, -5.747659e-3f, -5.703508e-3f, -5.643499e-3f,
    -5.567469e-3f, -5.475295e-3f, -5.366897e-3f, -5.242236e-3f, -5.101320e-3f,
    -4.944200e-3f, -4.770971e-3f, -4.581776e-3f, -4.376805e-3f, -4.156292e-3f,
    -3.920519e-3f, -3.669816e-3f, -3.404559e-3f, -3.125170e-3f, -2.832118e-3f,
    -2.525918e-3f, -2.207129e-3f, -1.876357e-3f, -1.534249e-3f, -1.181495e-3f,
    -8.188282e-4f, -4.470197e-4f, -6.688077e-5f, +3.207408e-4f, +7.149614e-4f,
    +1.114864e-3f, +1.519500e-3f, +1.927889e-3f, +2.339027e-3f, +2.751881e-3f,
    +3.165398e-3f, +3.578501e-3f, +3.990098e-3f, +4.399080e-3f, +4.804328e-3f,
    +5.204711e-3f, +5.599091e-3f, +5.986328e-3f, +6.365281e-3f, +6.734808e-3f,
    +7.093777e-3f, +7.441062e-3f, +7.775548e-3f, +8.096137e-3f, +8.401748e-3f,
    +8.691320e-3f, +8.963819e-3f, +9.218236e-3f, +9.453595e-3f, +9.668952e-3f,
    +9.863402e-3f, +1.003608e-2f, +1.018616e-2f, +1.031286e-2f, +1.041546e-2f,
    +1.049328e-2f, +1.054569e-2f, +1.057214e-2f, +1.057210e-2f, +1.054514e-2f,
    +1.049086e-2f, +1.040896e-2f, +1.029918e-2f, +1.016133e-2f, +9.995313e-3f,
    +9.801081e-3f, +9.578669e-3f, +9.328185e-3f, +9.049812e-3f, +8.743808e-3f,
    +8.410507e-3f, +8.050322e-3f, +7.663740e-3f, +7.251326e-3f, +6.813720e-3f,
    +6.351639e-3f, +5.865875e-3f, +5.357293e-3f, +4.826832e-3f, +4.275502e-3f,
    +3.704384e-3f, +3.114625e-3f, +2.507440e-3f, +1.884108e-3f, +1.245971e-3f,
    +5.944271e-4f, -6.906694e-5f, -7.430015e-4f, -1.425817e-3f, -2.115906e-3f,
    -2.811618e-3f, -3.511264e-3f, -4.213116e-3f, -4.915417e-3f, -5.616380e-3f,
    -6.314195e-3f, -7.007033e-3f, -7.693049e-3f, -8.370388e-3f, -9.037191e-3f,
    -9.691595e-3f, -1.033174e-2f, -1.095579e-2f, -1.156189e-2f, -1.214824e-2f,
    -1.271303e-2f, -1.325452e-2f, -1.377096e-2f, -1.426066e-2f, -1.472197e-2f,
    -1.515330e-2f, -1.555309e-2f, -1.591985e-2f, -1.625216e-2f, -1.654866e-2f,
    -1.680806e-2f, -1.702914e-2f, -1.721078e-2f, -1.735191e-2f, -1.745159e-2f,
    -1.750895e-2f, -1.752321e-2f, -1.749369e-2f, -1.741983e-2f, -1.730115e-2f,
    -1.713729e-2f, -1.692801e-2f, -1.667316e-2f, -1.637272e-2f, -1.602677e-2f,
    -1.563553e-2f, -1.519932e-2f, -1.471858e-2f, -1.419388e-2f, -1.362591e-2f,
    -1.301545e-2f, -1.236344e-2f, -1.167092e-2f, -1.093904e-2f, -1.016908e-2f,
    -9.362426e-3f, -8.520579e-3f, -7.645152e-3f, -6.737864e-3f, -5.800538e-3f,
    -4.835101e-3f, -3.843578e-3f, -2.828085e-3f, -1.790834e-3f, -7.341172e-4f,
    +3.396878e-4f, +1.428129e-3f, +2.528681e-3f, +3.638756e-3f, +4.755703e-3f,
    +5.876818e-3f, +6.999347e-3f, +8.120498e-3f, +9.237438e-3f, +1.034731e-2f,
    +1.144723e-2f, +1.253431e-2f, +1.360564e-2f, +1.465832e-2f, +1.568945e-2f,
    +1.669614e-2f, +1.767553e-2f, +1.862479e-2f, +1.954113e-2f, +2.042178e-2f,
    +2.126405e-2f, +2.206530e-2f, +2.282294e-2f, +2.353447e-2f, +2.419748e-2f,
    +2.480963e-2f, +2.536867e-2f, +2.587248e-2f, +2.631903e-2f, +2.670639e-2f,
    +2.703279e-2f, +2.729655e-2f, +2.749615e-2f, +2.763020e-2f, +2.769745e-2f,
    +2.769680e-2f, +2.762731e-2f, +2.748819e-2f, +2.727883e-2f, +2.699876e-2f,
    +2.664771e-2f, +2.622555e-2f, +2.573236e-2f, +2.516837e-2f, +2.453400e-2f,
    +2.382984e-2f, +2.305669e-2f, +2.221550e-2f, +2.130742e-2f, +2.033376e-2f,
    +1.929605e-2f, +1.819596e-2f, +1.703536e-2f, +1.581628e-2f, +1.454094e-2f,
    +1.321171e-2f, +1.183115e-2f, +1.040195e-2f, +8.926982e-3f, +7.409262e-3f,
    +5.851951e-3f, +4.258351e-3f, +2.631901e-3f, +9.761639e-4f, -7.051737e-4f,
    -2.408314e-3f, -4.129352e-3f, -5.864287e-3f, -7.609031e-3f, -9.359414e-3f,
    -1.111120e-2f, -1.286008e-2f, -1.460170e-2f, -1.633168e-2f, -1.804559e-2f,
    -1.973899e-2f, -2.140741e-2f, -2.304641e-2f, -2.465154e-2f, -2.621838e-2f,
    -2.774254e-2f, -2.921969e-2f, -3.064553e-2f, -3.201585e-2f, -3.332650e-2f,
    -3.457343e-2f, -3.575270e-2f, -3.686046e-2f, -3.789299e-2f, -3.884671e-2f,
    -3.971818e-2f, -4.050410e-2f, -4.120136e-2f, -4.180699e-2f, -4.231823e-2f,
    -4.273250e-2f, -4.304741e-2f, -4.326081e-2f, -4.337074e-2f, -4.337547e-2f,
    -4.327349e-2f, -4.306356e-2f, -4.274466e-2f, -4.231602e-2f, -4.177713e-2f,
    -4.112774e-2f, -4.036787e-2f, -3.949779e-2f, -3.851806e-2f, -3.742949e-2f,
    -3.623319e-2f, -3.493053e-2f, -3.352315e-2f, -3.201298e-2f, -3.040222e-2f,
    -2.869333e-2f, -2.688905e-2f, -2.499239e-2f, -2.300662e-2f, -2.093527e-2f,
    -1.878213e-2f, -1.655124e-2f, -1.424687e-2f, -1.187353e-2f, -9.435970e-3f,
    -6.939152e-3f, -4.388252e-3f, -1.788646e-3f, +8.540941e-4f, +3.534217e-3f,
    +6.245800e-3f, +8.982760e-3f, +1.173887e-2f, +1.450776e-2f, +1.728294e-2f,
    +2.005783e-2f, +2.282574e-2f, +2.557989e-2f, +2.831346e-2f, +3.101956e-2f,
    +3.369128e-2f, +3.632167e-2f, +3.890381e-2f, +4.143075e-2f, +4.389561e-2f,
    +4.629154e-2f, +4.861173e-2f, +5.084949e-2f, +5.299819e-2f, +5.505132e-2f,
    +5.700252e-2f, +5.884554e-2f, +6.057432e-2f, +6.218296e-2f, +6.366575e-2f,
    +6.501720e-2f, +6.623204e-2f, +6.730524e-2f, +6.823203e-2f, +6.900788e-2f,
    +6.962857e-2f, +7.009018e-2f, +7.038907e-2f, +7.052195e-2f, +7.048584e-2f,
    +7.027812e-2f, +6.989651e-2f, +6.933912e-2f, +6.860442e-2f, +6.769124e-2f,
    +6.659885e-2f, +6.532688e-2f, +6.387537e-2f, +6.224479e-2f, +6.043601e-2f,
    +5.845031e-2f, +5.628942e-2f, +5.395546e-2f, +5.145101e-2f, +4.877905e-2f,
    +4.594300e-2f, +4.294670e-2f, +3.979440e-2f, +3.649080e-2f, +3.304098e-2f,
    +2.945044e-2f, +2.572511e-2f, +2.187127e-2f, +1.789562e-2f, +1.380524e-2f,
    +9.607558e-3f, +5.310387e-3f, +9.218738e-4f, -3.549496e-3f, -8.094915e-3f,
    -1.270526e-2f, -1.737113e-2f, -2.208283e-2f, -2.683041e-2f, -3.160366e-2f,
    -3.639217e-2f, -4.118529e-2f, -4.597220e-2f, -5.074191e-2f, -5.548326e-2f,
    -6.018498e-2f, -6.483567e-2f, -6.942385e-2f, -7.393799e-2f, -7.836650e-2f,
    -8.269775e-2f, -8.692015e-2f, -9.102211e-2f, -9.499209e-2f, -9.881862e-2f,
    -1.024903e-1f, -1.059960e-1f, -1.093244e-1f, -1.124646e-1f, -1.154060e-1f,
    -1.181379e-1f, -1.206499e-1f, -1.229321e-1f, -1.249746e-1f, -1.267680e-1f,
    -1.283030e-1f, -1.295708e-1f, -1.305630e-1f, -1.312714e-1f, -1.316884e-1f,
    -1.318067e-1f, -1.316195e-1f, -1.311204e-1f, -1.303034e-1f, -1.291632e-1f,
    -1.276949e-1f, -1.258940e-1f, -1.237567e-1f, -1.212796e-1f, -1.184600e-1f,
    -1.152957e-1f, -1.117850e-1f, -1.079268e-1f, -1.037208e-1f, -9.916690e-2f,
    -9.426596e-2f, -8.901926e-2f, -8.342874e-2f, -7.749692e-2f, -7.122696e-2f,
    -6.462260e-2f, -5.768818e-2f, -5.042867e-2f, -4.284962e-2f, -3.495716e-2f,
    -2.675803e-2f, -1.825953e-2f, -9.469532e-3f, -3.964672e-4f, +8.950685e-3f,
    +1.856241e-2f, +2.842868e-2f, +3.853894e-2f, +4.888217e-2f, +5.944685e-2f,
    +7.022102e-2f, +8.119227e-2f, +9.234778e-2f, +1.036743e-1f, +1.151583e-1f,
    +1.267857e-1f, +1.385423e-1f, +1.504134e-1f, +1.623842e-1f, +1.744395e-1f,
    +1.865638e-1f, +1.987417e-1f, +2.109573e-1f, +2.231946e-1f, +2.354375e-1f,
    +2.476700e-1f, +2.598756e-1f, +2.720381e-1f, +2.841412e-1f, +2.961685e-1f,
    +3.081037e-1f, +3.199307e-1f, +3.316332e-1f, +3.431952e-1f, +3.546010e-1f,
    +3.658347e-1f, +3.768810e-1f, +3.877245e-1f, +3.983503e-1f, +4.087437e-1f,
    +4.188902e-1f, +4.287759e-1f, +4.383869e-1f, +4.477100e-1f, +4.567323e-1f,
    +4.654413e-1f, +4.738249e-1f, +4.818717e-1f, +4.895705e-1f, +4.969109e-1f,
    +5.038829e-1f, +5.104769e-1f, +5.166841e-1f, +5.224962e-1f, +5.279055e-1f,
    +5.329050e-1f, +5.374880e-1f, +5.416489e-1f, +5.453824e-1f, +5.486839e-1f,
    +5.515497e-1f, +5.539765e-1f, +5.559617e-1f, +5.575035e-1f, +5.586007e-1f,
    +5.592529e-1f, +5.594601e-1f, +5.592233e-1f, +5.585440e-1f, +5.574243e-1f,
    +5.558672e-1f, +5.538762e-1f, +5.514555e-1f, +5.486100e-1f, +5.453450e-1f,
    +5.416666e-1f, +5.375817e-1f, +5.330975e-1f, +5.282219e-1f, +5.229633e-1f,
    +5.173308e-1f, +5.113339e-1f, +5.049827e-1f, +4.982877e-1f, +4.912601e-1f,
    +4.839113e-1f, +4.762532e-1f, +4.682982e-1f, +4.600591e-1f, +4.515489e-1f,
    +4.427812e-1f, +4.337696e-1f, +4.245283e-1f, +4.150715e-1f, +4.054139e-1f,
    +3.955702e-1f, +3.855553e-1f, +3.753845e-1f, +3.650729e-1f, +3.546359e-1f,
    +3.440890e-1f, +3.334475e-1f, +3.227271e-1f, +3.119432e-1f, +3.011112e-1f,
    +2.902466e-1f, +2.793647e-1f, +2.684806e-1f, +2.576094e-1f, +2.467660e-1f,
    +2.359650e-1f, +2.252209e-1f, +2.145481e-1f, +2.039603e-1f, +1.934713e-1f,
    +1.830944e-1f, +1.728427e-1f, +1.627288e-1f, +1.527650e-1f, +1.429632e-1f,
    +1.333349e-1f, +1.238911e-1f, +1.146426e-1f, +1.055993e-1f, +9.677092e-2f,
    +8.816672e-2f, +7.979532e-2f, +7.166490e-2f, +6.378307e-2f, +5.615693e-2f,
    +4.879304e-2f, +4.169740e-2f, +3.487545e-2f, +2.833209e-2f, +2.207163e-2f,
    +1.609784e-2f, +1.041389e-2f, +5.022401e-3f, -7.457179e-5f, -4.875547e-3f,
    -9.379605e-3f, -1.358638e-2f, -1.749607e-2f, -2.110942e-2f, -2.442769e-2f,
    -2.745270e-2f, -3.018678e-2f, -3.263278e-2f, -3.479404e-2f, -3.667440e-2f,
    -3.827815e-2f, -3.961008e-2f, -4.067539e-2f, -4.147974e-2f, -4.202918e-2f,
    -4.233018e-2f, -4.238957e-2f, -4.221456e-2f, -4.181270e-2f, -4.119184e-2f,
    -4.036017e-2f, -3.932615e-2f, -3.809848e-2f, -3.668614e-2f, -3.509831e-2f,
    -3.334437e-2f, -3.143387e-2f, -2.937655e-2f, -2.718223e-2f, -2.486089e-2f,
    -2.242257e-2f, -1.987739e-2f, -1.723552e-2f, -1.450712e-2f, -1.170240e-2f,
    -8.831519e-3f, -5.904596e-3f, -2.931697e-3f, +7.719945e-5f, +3.112217e-3f,
    +6.163604e-3f, +9.221748e-3f, +1.227720e-2f, +1.532069e-2f, +1.834315e-2f,
    +2.133572e-2f, +2.428976e-2f, +2.719691e-2f, +3.004904e-2f, +3.283830e-2f,
    +3.555715e-2f, +3.819834e-2f, +4.075492e-2f, +4.322029e-2f, +4.558818e-2f,
    +4.785266e-2f, +5.000814e-2f, +5.204944e-2f, +5.397169e-2f, +5.577044e-2f,
    +5.744160e-2f, +5.898147e-2f, +6.038674e-2f, +6.165448e-2f, +6.278217e-2f,
    +6.376767e-2f, +6.460923e-2f, +6.530551e-2f, +6.585554e-2f, +6.625873e-2f,
    +6.651491e-2f, +6.662425e-2f, +6.658732e-2f, +6.640503e-2f, +6.607868e-2f,
    +6.560990e-2f, +6.500067e-2f, +6.425332e-2f, +6.337049e-2f, +6.235514e-2f,
    +6.121053e-2f, +5.994022e-2f, +5.854804e-2f, +5.703812e-2f, +5.541479e-2f,
    +5.368268e-2f, +5.184660e-2f, +4.991161e-2f, +4.788295e-2f, +4.576604e-2f,
    +4.356649e-2f, +4.129004e-2f, +3.894258e-2f, +3.653012e-2f, +3.405878e-2f,
    +3.153476e-2f, +2.896433e-2f, +2.635385e-2f, +2.370968e-2f, +2.103824e-2f,
    +1.834594e-2f, +1.563919e-2f, +1.292438e-2f, +1.020787e-2f, +7.495951e-3f,
    +4.794868e-3f, +2.110777e-3f, -5.502614e-4f, -3.182294e-3f, -5.779488e-3f,
    -8.336145e-3f, -1.084672e-2f, -1.330581e-2f, -1.570820e-2f, -1.804885e-2f,
    -2.032292e-2f, -2.252575e-2f, -2.465290e-2f, -2.670018e-2f, -2.866357e-2f,
    -3.053934e-2f, -3.232397e-2f, -3.401419e-2f, -3.560700e-2f, -3.709965e-2f,
    -3.848964e-2f, -3.977475e-2f, -4.095303e-2f, -4.202280e-2f, -4.298264e-2f,
    -4.383142e-2f, -4.456827e-2f, -4.519261e-2f, -4.570412e-2f, -4.610273e-2f,
    -4.638869e-2f, -4.656246e-2f, -4.662479e-2f, -4.657668e-2f, -4.641939e-2f,
    -4.615441e-2f, -4.578349e-2f, -4.530859e-2f, -4.473193e-2f, -4.405591e-2f,
    -4.328316e-2f, -4.241654e-2f, -4.145906e-2f, -4.041394e-2f, -3.928457e-2f,
    -3.807452e-2f, -3.678749e-2f, -3.542734e-2f, -3.399808e-2f, -3.250382e-2f,
    -3.094879e-2f, -2.933733e-2f, -2.767387e-2f, -2.596290e-2f, -2.420900e-2f,
    -2.241680e-2f, -2.059096e-2f, -1.873621e-2f, -1.685725e-2f, -1.495883e-2f,
    -1.304567e-2f, -1.112251e-2f, -9.194026e-3f, -7.264887e-3f, -5.339704e-3f,
    -3.423034e-3f, -1.519366e-3f, +3.668890e-4f, +2.231407e-3f, +4.069961e-3f,
    +5.878431e-3f, +7.652810e-3f, +9.389215e-3f, +1.108390e-2f, +1.273324e-2f,
    +1.433379e-2f, +1.588222e-2f, +1.737539e-2f, +1.881031e-2f, +2.018417e-2f,
    +2.149433e-2f, +2.273832e-2f, +2.391389e-2f, +2.501895e-2f, +2.605161e-2f,
    +2.701016e-2f, +2.789312e-2f, +2.869918e-2f, +2.942723e-2f, +3.007638e-2f,
    +3.064593e-2f, +3.113536e-2f, +3.154439e-2f, +3.187289e-2f, +3.212097e-2f,
    +3.228890e-2f, +3.237717e-2f, +3.238643e-2f, +3.231752e-2f, +3.217149e-2f,
    +3.194952e-2f, +3.165299e-2f, +3.128345e-2f, +3.084258e-2f, +3.033226e-2f,
    +2.975447e-2f, +2.911137e-2f, +2.840524e-2f, +2.763848e-2f, +2.681364e-2f,
    +2.593334e-2f, +2.500034e-2f, +2.401749e-2f, +2.298773e-2f, +2.191408e-2f,
    +2.079964e-2f, +1.964756e-2f, +1.846107e-2f, +1.724343e-2f, +1.599794e-2f,
    +1.472794e-2f, +1.343680e-2f, +1.212790e-2f, +1.080460e-2f, +9.470301e-3f,
    +8.128363e-3f, +6.782139e-3f, +5.434954e-3f, +4.090097e-3f, +2.750817e-3f,
    +1.420311e-3f, +1.017216e-4f, -1.201875e-3f, -2.487472e-3f, -3.752140e-3f,
    -4.993035e-3f, -6.207402e-3f, -7.392582e-3f, -8.546017e-3f, -9.665256e-3f,
    -1.074796e-2f, -1.179190e-2f, -1.279498e-2f, -1.375521e-2f, -1.467075e-2f,
    -1.553987e-2f, -1.636098e-2f, -1.713263e-2f, -1.785351e-2f, -1.852244e-2f,
    -1.913839e-2f, -1.970046e-2f, -2.020791e-2f, -2.066013e-2f, -2.105667e-2f,
    -2.139718e-2f, -2.168151e-2f, -2.190961e-2f, -2.208157e-2f, -2.219765e-2f,
    -2.225821e-2f, -2.226375e-2f, -2.221491e-2f, -2.211245e-2f, -2.195727e-2f,
    -2.175035e-2f, -2.149283e-2f, -2.118594e-2f, -2.083102e-2f, -2.042951e-2f,
    -1.998296e-2f, -1.949299e-2f, -1.896135e-2f, -1.838982e-2f, -1.778030e-2f,
    -1.713474e-2f, -1.645516e-2f, -1.574365e-2f, -1.500234e-2f, -1.423342e-2f,
    -1.343912e-2f, -1.262170e-2f, -1.178345e-2f, -1.092670e-2f, -1.005378e-2f,
    -9.167041e-3f, -8.268841e-3f, -7.361534e-3f, -6.447470e-3f, -5.528988e-3f,
    -4.608410e-3f, -3.688035e-3f, -2.770132e-3f, -1.856938e-3f, -9.506506e-4f,
    -5.342431e-5f, +8.326361e-4f, +1.705479e-3f, +2.563111e-3f, +3.403601e-3f,
    +4.225084e-3f, +5.025766e-3f, +5.803925e-3f, +6.557919e-3f, +7.286186e-3f,
    +7.987246e-3f, +8.659707e-3f, +9.302264e-3f, +9.913705e-3f, +1.049291e-2f,
    +1.103885e-2f, +1.155060e-2f, +1.202733e-2f, +1.246830e-2f, +1.287287e-2f,
    +1.324052e-2f, +1.357079e-2f, +1.386337e-2f, +1.411799e-2f, +1.433453e-2f,
    +1.451294e-2f, +1.465328e-2f, +1.475568e-2f, +1.482040e-2f, +1.484775e-2f,
    +1.483818e-2f, +1.479217e-2f, +1.471033e-2f, +1.459334e-2f, +1.444195e-2f,
    +1.425698e-2f, +1.403936e-2f, +1.379005e-2f, +1.351011e-2f, +1.320063e-2f,
    +1.286278e-2f, +1.249779e-2f, +1.210694e-2f, +1.169154e-2f, +1.125296e-2f,
    +1.079263e-2f, +1.031197e-2f, +9.812466e-3f, +9.295627e-3f, +8.762978e-3f,
    +8.216069e-3f, +7.656462e-3f, +7.085733e-3f, +6.505463e-3f, +5.917236e-3f,
    +5.322636e-3f, +4.723241e-3f, +4.120618e-3f, +3.516324e-3f, +2.911896e-3f,
    +2.308852e-3f, +1.708685e-3f, +1.112861e-3f, +5.228143e-4f, -6.005633e-5f,
    -6.343884e-4f, -1.198860e-3f, -1.752195e-3f, -2.293159e-3f, -2.820570e-3f,
    -3.333297e-3f, -3.830260e-3f, -4.310436e-3f, -4.772859e-3f, -5.216622e-3f,
    -5.640879e-3f, -6.044843e-3f, -6.427795e-3f, -6.789075e-3f, -7.128091e-3f,
    -7.444315e-3f, -7.737285e-3f, -8.006607e-3f, -8.251951e-3f, -8.473054e-3f,
    -8.669719e-3f, -8.841814e-3f, -8.989272e-3f, -9.112093e-3f, -9.210335e-3f,
    -9.284123e-3f, -9.333641e-3f, -9.359132e-3f, -9.360899e-3f, -9.339299e-3f,
    -9.294747e-3f, -9.227709e-3f, -9.138702e-3f, -9.028293e-3f, -8.897093e-3f,
    -8.745760e-3f, -8.574994e-3f, -8.385533e-3f, -8.178154e-3f, -7.953665e-3f,
    -7.712911e-3f, -7.456761e-3f, -7.186114e-3f, -6.901890e-3f, -6.605034e-3f,
    -6.296504e-3f, -5.977277e-3f, -5.648342e-3f, -5.310695e-3f, -4.965342e-3f,
    -4.613293e-3f, -4.255557e-3f, -3.893145e-3f, -3.527061e-3f, -3.158305e-3f,
    -2.787866e-3f, -2.416723e-3f, -2.045841e-3f, -1.676167e-3f, -1.308632e-3f,
    -9.441435e-4f, -5.835884e-4f, -2.278277e-4f, +1.223041e-4f, +4.660010e-4f,
    +8.024873e-4f, +1.131019e-3f, +1.450886e-3f, +1.761412e-3f, +2.061957e-3f,
    +2.351918e-3f, +2.630731e-3f, +2.897870e-3f, +3.152849e-3f, +3.395222e-3f,
    +3.624585e-3f, +3.840575e-3f, +4.042870e-3f, +4.231191e-3f, +4.405301e-3f,
    +4.565003e-3f, +4.710145e-3f, +4.840613e-3f, +4.956336e-3f, +5.057284e-3f,
    +5.143466e-3f, +5.214930e-3f, +5.271764e-3f, +5.314093e-3f, +5.342078e-3f,
    +5.355915e-3f, +5.355838e-3f, +5.342109e-3f, +5.315026e-3f, +5.274915e-3f,
    +5.222134e-3f, +5.157066e-3f, +5.080121e-3f, +4.991734e-3f, +4.892362e-3f,
    +4.782485e-3f, +4.662600e-3f, +4.533223e-3f, +4.394887e-3f, +4.248139e-3f};

void MuxerInit(Muxer* muxer) {
}

int MuxerProcessSamples(Muxer* muxer, const float* tactile_input,
                        int num_frames, float* audio_output) {
  int c;
  for (c = 0; c < kMuxTactileChannels; ++c) {
    const float* input = tactile_input + c;

    int i;
    for (i = 0; i < num_frames; ++i) {
      memmove(channel->buffer, channel->buffer + 1,
              (kLpfNumTaps - 1) * sizeof(ComplexFloat));
      /* Shift band midpoint down to DC. */
      channel->buffer[kLpfNumTaps - 1] = ComplexFloatMulReal(
          OscillatorComplexExp(&channel->down_converter), input[i]);
      OscillatorNext(&channel->down_converter);

      int j;
      for (j = 0; j < kMuxTactileRateFactor; ++j) {
        const int upsample_phase =
            (kMuxTactileRateFactor - j) % kMuxTactileRateFactor;
        ComplexFloat sum = ComplexFloat(0.0f, 0.0f);
        int k;
        for (k = upsample_phase; k < kLpfNumTaps; ++k) {
          sum = ComplexFloatAdd(
              sum,
              ComplexFloatMulReal(channel->buffer[k / kMuxTactileRateFactor],
                                  kWeaverLpf[kLpfNumTaps - 1 - k]));
        }
      }
    }
  }
}