/* Copyright 2019 Google LLC
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
 *
 *
 * Constants and trained network parameters for the vowel embedding network.
 */

#ifndef AUDIO_TO_TACTILE_SRC_PHONETICS_EMBED_VOWEL_PARAMS_H_
#define AUDIO_TO_TACTILE_SRC_PHONETICS_EMBED_VOWEL_PARAMS_H_

/* Number of CARL channels in a frame. */
#define kNumChannels 56

/* Number of units in the fully connected layers. */
#define kDense1Units 16
#define kDense2Units 16
#define kDense3Units 2

static const float kDense1Weights[kNumChannels * kDense1Units] = {-0.190976f,
  -0.210734f, -0.238540f, -0.240570f, -0.199742f, -0.137206f, -0.076723f,
  -0.023542f, 0.006658f, 0.022935f, 0.030526f, 0.031020f, 0.073314f, 0.161881f,
  0.184120f, 0.099725f, 0.037379f, 0.069144f, 0.181255f, 0.323469f, 0.375901f,
  0.263087f, 0.072905f, -0.023134f, -0.012068f, -0.027050f, -0.105615f,
  -0.139352f, -0.063929f, 0.017984f, 0.043612f, 0.027121f, 0.006540f, 0.017063f,
  0.071489f, 0.134880f, 0.141715f, 0.085962f, -0.006745f, -0.134393f,
  -0.227155f, -0.197199f, -0.166272f, -0.174661f, -0.087792f, 0.069278f,
  0.167597f, 0.302261f, 0.322220f, 0.266622f, 0.203741f, 0.121207f, 0.077709f,
  0.164549f, 0.201143f, 0.077832f, -0.049828f, -0.001243f, 0.058155f, 0.101758f,
  0.114277f, 0.082423f, -0.003675f, -0.108471f, -0.165607f, -0.139071f,
  -0.024598f, 0.105671f, 0.144655f, 0.084694f, -0.007204f, -0.081982f,
  -0.114451f, -0.118293f, -0.126179f, -0.123938f, -0.101280f, -0.087675f,
  -0.130753f, -0.242893f, -0.374250f, -0.442865f, -0.369212f, -0.135955f,
  0.188517f, 0.433024f, 0.512903f, 0.423971f, 0.244052f, 0.116740f, 0.074744f,
  0.041927f, -0.046421f, -0.157298f, -0.160466f, -0.052091f, 0.027108f,
  0.052467f, 0.045163f, 0.020923f, 0.024030f, 0.030118f, 0.000706f, 0.015530f,
  -0.015968f, -0.081561f, -0.058178f, 0.041301f, 0.050203f, 0.061413f,
  0.169478f, 0.271399f, 0.165797f, 0.140707f, 0.130499f, 0.138251f, 0.160044f,
  0.167828f, 0.120931f, 0.044331f, -0.003519f, -0.007675f, 0.001797f, 0.016386f,
  -0.002856f, -0.081450f, -0.130274f, -0.086839f, 0.025992f, 0.200188f,
  0.330440f, 0.265689f, -0.005403f, -0.333061f, -0.499921f, -0.399802f,
  -0.166537f, 0.043979f, 0.166185f, 0.179323f, 0.124343f, 0.099059f, 0.107185f,
  0.085573f, 0.064061f, 0.051620f, 0.049437f, 0.028948f, 0.043394f, 0.077061f,
  0.054467f, 0.016350f, 0.033264f, 0.055509f, -0.014349f, -0.090730f,
  -0.069660f, -0.115065f, -0.195678f, -0.283885f, -0.194536f, -0.125105f,
  -0.102681f, 0.000624f, 0.093569f, -0.007823f, 0.026556f, 0.300219f, 0.180212f,
  0.145838f, 0.100697f, 0.049574f, -0.003951f, -0.040915f, -0.054691f,
  -0.063274f, -0.080479f, -0.110840f, -0.152808f, -0.195299f, -0.222665f,
  -0.243964f, -0.285438f, -0.358233f, -0.449991f, -0.536693f, -0.580635f,
  -0.518903f, -0.318288f, -0.027263f, 0.236836f, 0.360061f, 0.319320f,
  0.196632f, 0.097501f, 0.055814f, 0.054104f, 0.061130f, 0.077710f, 0.104198f,
  0.096079f, 0.030769f, -0.047035f, -0.111405f, -0.154128f, -0.124348f,
  -0.059740f, -0.031145f, -0.013834f, 0.015271f, 0.047685f, 0.065480f,
  0.045853f, -0.006601f, -0.045436f, -0.031025f, -0.079958f, -0.077902f,
  0.010085f, 0.028174f, 0.001056f, 0.081138f, 0.075858f, -0.019460f, -0.362222f,
  -0.261987f, -0.128374f, -0.012055f, 0.047544f, 0.045016f, 0.019676f,
  0.002296f, 0.010286f, 0.027525f, 0.031623f, 0.067469f, 0.138694f, 0.154657f,
  0.075568f, -0.012633f, -0.029706f, 0.021978f, 0.109771f, 0.198286f, 0.235071f,
  0.187789f, 0.121020f, 0.089626f, 0.089515f, 0.079919f, 0.012292f, -0.101701f,
  -0.215616f, -0.263449f, -0.211689f, -0.100205f, -0.001514f, 0.045177f,
  0.000970f, -0.087455f, -0.142473f, -0.177899f, -0.175942f, -0.097844f,
  -0.107934f, -0.162873f, -0.119327f, -0.078105f, -0.026909f, 0.142779f,
  0.301816f, 0.378522f, 0.293813f, 0.141260f, 0.126032f, 0.074101f, -0.040211f,
  -0.016974f, 0.001372f, -0.114856f, 0.093946f, 0.086668f, 0.105596f, 0.136173f,
  0.147050f, 0.145399f, 0.119225f, 0.055644f, -0.028326f, -0.105836f,
  -0.133078f, -0.092502f, -0.066438f, -0.085996f, -0.040637f, 0.070756f,
  0.124238f, 0.100452f, 0.023446f, -0.071352f, -0.034634f, 0.219493f, 0.468516f,
  0.409664f, 0.085127f, -0.182377f, -0.243196f, -0.258333f, -0.350746f,
  -0.397618f, -0.338030f, -0.258551f, -0.178284f, -0.106851f, -0.039900f,
  0.022699f, 0.122911f, 0.221494f, 0.271598f, 0.273424f, 0.254649f, 0.157309f,
  0.016881f, -0.027579f, -0.013424f, -0.036510f, -0.049060f, -0.134378f,
  -0.090680f, 0.015280f, -0.056061f, -0.047529f, 0.117774f, -0.027975f,
  -0.154375f, 0.197320f, 0.095255f, 0.022566f, -0.096951f, -0.190582f,
  -0.188415f, -0.048157f, 0.152200f, 0.204020f, 0.030571f, -0.085847f,
  0.060672f, 0.163462f, 0.023409f, -0.125535f, -0.142092f, -0.053075f,
  0.112593f, 0.171506f, 0.037885f, -0.123748f, -0.131014f, 0.033912f, 0.171615f,
  0.101765f, -0.026828f, -0.026412f, 0.030565f, 0.032793f, -0.025288f,
  -0.054276f, -0.075124f, -0.013745f, -0.023350f, -0.114201f, -0.078823f,
  0.036320f, 0.030141f, 0.041666f, 0.086987f, 0.036984f, -0.009636f, 0.040019f,
  0.072646f, 0.035628f, -0.044130f, 0.050458f, 0.088864f, 0.022805f, -0.229535f,
  -0.162321f, 0.143450f, 0.147288f, 0.010756f, -0.033966f, -0.405101f,
  -1.137337f, -0.207507f, -0.178703f, -0.128504f, -0.072539f, -0.018819f,
  0.053108f, 0.136219f, 0.180592f, 0.127860f, -0.001501f, -0.095950f,
  -0.080628f, 0.000293f, 0.054587f, 0.034460f, -0.034892f, -0.063555f,
  -0.027899f, -0.005081f, -0.041794f, -0.085758f, -0.059105f, 0.019257f,
  0.057819f, 0.050414f, 0.065730f, 0.095769f, 0.090544f, 0.066225f, 0.075974f,
  0.068963f, 0.025649f, -0.006985f, -0.063620f, -0.134019f, -0.188366f,
  -0.253891f, -0.290607f, -0.165438f, 0.034702f, 0.211103f, 0.257917f,
  0.233861f, 0.240090f, 0.199099f, 0.058885f, -0.071355f, -0.203219f,
  -0.078973f, 0.052255f, -0.123667f, -0.129070f, 0.197002f, 0.144256f,
  0.046336f, 0.474546f, -0.193261f, -0.182385f, -0.148051f, -0.093104f,
  -0.020398f, 0.043145f, 0.053951f, 0.017664f, -0.010767f, 0.008926f, 0.076439f,
  0.145271f, 0.143293f, 0.073197f, 0.046779f, 0.110322f, 0.174755f, 0.158862f,
  0.040516f, -0.111028f, -0.130683f, 0.063596f, 0.306938f, 0.346976f, 0.145722f,
  -0.084266f, -0.176719f, -0.160191f, -0.084531f, 0.049390f, 0.187911f,
  0.254328f, 0.258057f, 0.233122f, 0.199346f, 0.146695f, 0.085586f, -0.016276f,
  -0.167682f, -0.221036f, -0.157931f, -0.105821f, -0.085296f, -0.024199f,
  0.080500f, 0.174722f, 0.203918f, 0.074808f, 0.006687f, -0.003722f, -0.006310f,
  0.052551f, 0.108759f, 0.029889f, 0.028513f, 0.143485f, -0.247254f, -0.216300f,
  -0.170322f, -0.119845f, -0.078325f, -0.051130f, -0.016584f, 0.043554f,
  0.120166f, 0.171183f, 0.165644f, 0.111042f, 0.055334f, 0.047700f, 0.084154f,
  0.119548f, 0.123303f, 0.109552f, 0.106223f, 0.129831f, 0.166858f, 0.201077f,
  0.243229f, 0.303438f, 0.367983f, 0.407611f, 0.399501f, 0.340065f, 0.240671f,
  0.126228f, 0.015234f, -0.084077f, -0.156782f, -0.169606f, -0.145554f,
  -0.119650f, -0.109073f, -0.077797f, 0.005468f, 0.065462f, 0.024092f,
  -0.039679f, -0.041821f, 0.003357f, 0.017032f, 0.024557f, 0.031962f,
  -0.023727f, -0.037728f, -0.056114f, -0.038544f, 0.026462f, 0.023613f,
  -0.017309f, -0.012374f, -0.159528f, -0.035787f, 0.028702f, 0.104653f,
  0.166439f, 0.205297f, 0.213091f, 0.208522f, 0.194232f, 0.155687f, 0.095974f,
  0.002542f, -0.133680f, -0.251427f, -0.273679f, -0.169838f, 0.028555f,
  0.186642f, 0.166887f, 0.010723f, -0.101278f, -0.081478f, 0.000032f, 0.040946f,
  0.016498f, -0.025201f, -0.037480f, -0.024732f, -0.002384f, 0.004832f,
  -0.002937f, -0.018927f, -0.053698f, -0.092953f, -0.103830f, -0.114812f,
  -0.123476f, -0.136809f, -0.135163f, -0.110404f, -0.076821f, 0.050034f,
  0.204673f, 0.247000f, 0.130684f, -0.076275f, -0.210951f, -0.146509f,
  0.065827f, 0.258466f, 0.295404f, 0.139216f, -0.108136f, -0.275116f,
  -0.298108f, -0.324366f, -0.420670f, -0.397385f, -0.334527f, -0.239248f,
  -0.111412f, 0.056921f, 0.158472f, 0.129926f, 0.054792f, 0.018208f, 0.014628f,
  0.043902f, 0.118597f, 0.155681f, 0.096545f, 0.026881f, 0.056629f, 0.173795f,
  0.283329f, 0.281636f, 0.150442f, 0.043165f, 0.049071f, 0.013332f, -0.140020f,
  -0.308457f, -0.375519f, -0.315329f, -0.203412f, -0.116252f, -0.064371f,
  -0.068329f, -0.123827f, -0.154690f, -0.100629f, 0.022302f, 0.124732f,
  0.134682f, 0.051056f, -0.040871f, -0.045295f, -0.061479f, -0.134009f,
  -0.147680f, -0.075994f, -0.024893f, -0.022779f, 0.033981f, 0.152718f,
  0.201583f, 0.166615f, 0.229094f, 0.185059f, 0.081670f, 0.179968f, 0.202292f,
  -0.216500f, -0.092312f, -0.046294f, 0.021843f, 0.071145f, 0.063217f,
  0.026116f, 0.025218f, 0.066695f, 0.122227f, 0.134062f, 0.065554f, -0.029452f,
  -0.061319f, -0.007666f, 0.089924f, 0.172493f, 0.182485f, 0.115366f, 0.022336f,
  -0.068200f, -0.148052f, -0.205331f, -0.208835f, -0.138199f, -0.027736f,
  0.040658f, 0.048708f, 0.059896f, 0.116349f, 0.168226f, 0.175725f, 0.159046f,
  0.121839f, 0.095791f, 0.066875f, 0.003021f, -0.045474f, -0.043179f,
  -0.077645f, -0.198113f, -0.268268f, -0.148749f, 0.025518f, 0.132075f,
  0.212189f, 0.255898f, 0.188088f, 0.084493f, 0.070014f, 0.131610f, 0.133603f,
  0.071969f, 0.089713f, 0.176254f, 0.221640f, 0.282403f, 0.120247f, 0.122920f,
  0.112213f, 0.081674f, 0.041576f, 0.000422f, -0.017969f, 0.013468f, 0.075295f,
  0.098781f, 0.069487f, 0.035753f, 0.045179f, 0.107092f, 0.182999f, 0.199642f,
  0.096436f, -0.104725f, -0.288389f, -0.360434f, -0.325083f, -0.241021f,
  -0.160779f, -0.112754f, -0.096906f, -0.092960f, -0.071081f, -0.010421f,
  0.069032f, 0.091882f, 0.012603f, -0.084654f, -0.110978f, -0.080380f,
  -0.053851f, -0.038547f, -0.031883f, 0.016018f, 0.151523f, 0.236088f,
  0.167693f, -0.001128f, -0.140396f, -0.144188f, -0.041603f, 0.089547f,
  0.184276f, 0.196623f, 0.094084f, -0.022479f, -0.009274f, 0.007841f,
  -0.066573f, -0.073634f, -0.101078f, -0.248380f, -0.200967f, -0.169842f,
  -0.120753f, -0.061000f, 0.026795f, 0.099866f, 0.110927f, 0.086095f, 0.064121f,
  0.046897f, 0.038748f, 0.041148f, 0.031846f, 0.012570f, 0.038808f, 0.128069f,
  0.194930f, 0.160494f, 0.041651f, -0.069557f, -0.072450f, 0.042760f, 0.151688f,
  0.120610f, -0.037763f, -0.153924f, -0.122533f, -0.028449f, 0.025222f,
  0.022446f, -0.044690f, -0.115544f, -0.127802f, -0.102808f, -0.051490f,
  0.022615f, 0.130599f, 0.237763f, 0.271743f, 0.199604f, 0.163946f, 0.088733f,
  0.030441f, 0.055727f, 0.098327f, 0.049625f, 0.024760f, 0.052160f, 0.035185f,
  0.027819f, 0.031122f, -0.024491f, -0.096271f, -0.122294f, -0.106171f,
  -0.125870f, -0.164362f, -0.101158f, -0.034508f, 0.001255f, -0.004416f,
  -0.022259f, 0.002874f, 0.058806f, 0.103394f, 0.103376f, 0.055988f, 0.006797f,
  0.015109f, 0.059129f, 0.067169f, 0.055527f, 0.077703f, 0.109404f, 0.116700f,
  0.103355f, 0.063307f, -0.025462f, -0.124336f, -0.180899f, -0.202640f,
  -0.216384f, -0.192045f, -0.068585f, 0.133293f, 0.278092f, 0.303084f,
  0.242024f, 0.109284f, -0.050222f, -0.188038f, -0.302443f, -0.429948f,
  -0.491995f, -0.414906f, -0.248974f, -0.038351f, 0.148738f, 0.250114f,
  0.258889f, 0.224952f, 0.166179f, 0.073354f, 0.030693f, 0.015939f, 0.042892f,
  0.120391f, 0.183027f, 0.215356f, 0.281147f, 0.302744f, 0.243719f};

static const float kDense1Bias[kDense1Units] = {-0.123996f, 0.019809f,
  0.217024f, 0.029355f, 0.065803f, 0.046746f, -0.031317f, -0.161043f,
  -0.102670f, 0.077854f, -0.047038f, -0.070926f, -0.352098f, 0.112313f,
  -0.041143f, 0.211405f};

static const float kDense2Weights[kDense1Units * kDense2Units] = {1.422294f,
  0.157701f, -0.014483f, 1.014011f, -0.986168f, -0.331470f, -1.896671f,
  1.474017f, 0.568599f, 0.508272f, 0.135587f, -1.596775f, -0.285705f, 0.234758f,
  0.288734f, -0.370155f, -0.244858f, 1.279583f, 0.851840f, 1.106425f,
  -1.033685f, 1.090083f, -2.865289f, 0.316505f, 0.701219f, -0.020689f,
  -0.289977f, 1.290466f, 0.298121f, -0.199616f, -0.168845f, -0.465427f,
  -0.286003f, -0.362456f, -0.824576f, 0.835604f, 0.958069f, -1.013201f,
  3.069698f, 0.167341f, -0.570346f, 0.087601f, 1.554550f, -1.865748f, 0.599068f,
  0.679356f, 0.644059f, 1.303614f, -0.134100f, -0.326206f, -0.005171f,
  0.026429f, 1.231647f, 0.763624f, -0.305052f, -0.455173f, -0.104281f,
  -5.670186f, -1.183696f, 0.655602f, 0.333105f, -0.228827f, -0.182889f,
  0.013135f, -0.380650f, 0.206379f, -0.629997f, 1.723360f, 0.876768f, 0.367853f,
  -0.189256f, 0.436032f, -0.529548f, 0.367268f, -0.524420f, 0.132575f,
  -0.079175f, -0.661519f, 0.291349f, 0.305507f, 0.256189f, 1.150549f, 0.112773f,
  0.211983f, -0.551589f, -0.555186f, 0.106175f, -0.069692f, -0.234074f,
  -0.080499f, -0.179621f, 2.794378f, -0.016254f, 0.234093f, 0.312016f,
  -0.189532f, -0.000187f, 0.000198f, -0.000085f, 0.000159f, 0.000035f,
  0.000050f, -0.000106f, 0.000023f, -0.000114f, 0.000071f, -0.000002f,
  0.000079f, -0.000291f, 0.000066f, -0.000253f, -0.000062f, 0.724575f,
  1.929436f, 0.645836f, -0.629879f, -1.224515f, -0.141789f, -0.104391f,
  -0.000989f, 0.112935f, 0.148076f, -0.056938f, -0.837512f, -0.048966f,
  0.643413f, -0.215530f, -0.700595f, -0.486407f, 1.367630f, -0.344597f,
  0.730689f, 1.322393f, -1.076914f, 2.571315f, -2.085177f, -0.467598f,
  0.082971f, 1.350796f, -0.226090f, 0.761887f, 0.673998f, 0.416891f, 0.724166f,
  0.377798f, -1.011246f, 0.774446f, -4.213850f, -0.311371f, -0.057765f,
  0.491419f, -0.255862f, 0.282695f, -0.575960f, 0.325122f, 0.301859f,
  -0.056605f, 0.742837f, -0.274456f, 0.255075f, -0.409493f, 0.343300f,
  0.421559f, 1.061562f, 2.222602f, -0.731151f, 2.520866f, -2.313324f,
  -0.205738f, -0.002534f, 1.544629f, -0.512489f, 0.959957f, 0.879648f,
  -0.099663f, 0.722891f, -0.000381f, 0.000011f, 0.000179f, -0.000061f,
  0.000129f, -0.000033f, 0.000060f, 0.000292f, -0.000249f, -0.000049f,
  -0.000075f, 0.000086f, 0.000090f, 0.000291f, 0.000077f, -0.000200f,
  -0.713436f, 0.408516f, -1.259403f, 0.952130f, 0.790173f, -0.652498f,
  2.702441f, 0.827379f, -0.382968f, 0.150806f, 2.122021f, -1.491132f, 0.901154f,
  0.760603f, 0.995107f, 1.776618f, 1.802313f, 1.384286f, -2.233525f, -1.403135f,
  0.480425f, -2.500040f, 8.858876f, -1.647180f, -1.224868f, 0.075960f,
  2.423400f, -3.589697f, -0.027046f, -0.316089f, -0.738676f, 0.501493f,
  -0.224184f, -0.086190f, 0.592491f, 0.197766f, -1.919473f, 0.851109f,
  -0.096849f, 2.134432f, -0.327447f, 0.274452f, -0.796544f, -0.880751f,
  -0.087122f, -0.123680f, -0.229525f, -0.335398f, -0.192929f, -0.008533f,
  -0.816777f, 2.686821f, 0.152488f, 0.139878f, 1.758620f, -0.818561f,
  -0.599850f, 0.355536f, 0.725463f, -1.498010f, 1.101419f, 0.164312f,
  -0.888049f, 0.332267f};

static const float kDense2Bias[kDense2Units] = {0.028930f, 0.234767f, 0.089701f,
  0.001542f, -0.351285f, -0.041428f, -0.033662f, 0.602401f, -0.158875f,
  0.525943f, 0.038202f, -0.012932f, 0.284273f, -0.073814f, 0.439025f,
  0.114065f};

static const float kDense3Weights[kDense2Units * kDense3Units] = {-0.796153f,
  -0.560278f, 0.121138f, 4.432028f, -1.758547f, 0.487273f, 0.142651f, 1.403328f,
  -3.286591f, -1.199432f, 1.774344f, -0.101449f, 0.822271f, 24.992949f,
  -1.186845f, 3.550081f, 0.723969f, -1.367415f, -3.536124f, -6.919399f,
  -0.737804f, 1.632088f, -0.069592f, -1.475941f, 0.265598f, 0.431428f,
  1.128519f, -0.351772f, 1.740931f, -17.226662f, 0.737762f, 0.234357f};

static const float kDense3Bias[kDense3Units] = {-0.206937f, 0.428134f};

#endif /* AUDIO_TO_TACTILE_SRC_PHONETICS_EMBED_VOWEL_PARAMS_H_ */