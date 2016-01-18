/**
 Copyright (c) 2015 Eric Bruneton
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 3. Neither the name of the copyright holder nor the names of its contributors
 may be used to endorse or promote products derived from this software without
 specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "physics/cie.h"

#include <vector>

namespace {

struct Tables {
  std::vector<Dimensionless> x_bar_samples;
  std::vector<Dimensionless> y_bar_samples;
  std::vector<Dimensionless> z_bar_samples;

  Tables() {
    // Values from "CIE (1931) 2-deg color matching functions", see
    // "http://web.archive.org/web/20081228084047/
    //    http://www.cvrl.org/database/data/cmfs/ciexyz31.txt".
    Add(0.000000000000, 0.000000000000, 0.000000000000);
    Add(0.000129900000, 0.000003917000, 0.000606100000);
    Add(0.000232100000, 0.000006965000, 0.001086000000);
    Add(0.000414900000, 0.000012390000, 0.001946000000);
    Add(0.000741600000, 0.000022020000, 0.003486000000);
    Add(0.001368000000, 0.000039000000, 0.006450001000);
    Add(0.002236000000, 0.000064000000, 0.010549990000);
    Add(0.004243000000, 0.000120000000, 0.020050010000);
    Add(0.007650000000, 0.000217000000, 0.036210000000);
    Add(0.014310000000, 0.000396000000, 0.067850010000);
    Add(0.023190000000, 0.000640000000, 0.110200000000);
    Add(0.043510000000, 0.001210000000, 0.207400000000);
    Add(0.077630000000, 0.002180000000, 0.371300000000);
    Add(0.134380000000, 0.004000000000, 0.645600000000);
    Add(0.214770000000, 0.007300000000, 1.039050100000);
    Add(0.283900000000, 0.011600000000, 1.385600000000);
    Add(0.328500000000, 0.016840000000, 1.622960000000);
    Add(0.348280000000, 0.023000000000, 1.747060000000);
    Add(0.348060000000, 0.029800000000, 1.782600000000);
    Add(0.336200000000, 0.038000000000, 1.772110000000);
    Add(0.318700000000, 0.048000000000, 1.744100000000);
    Add(0.290800000000, 0.060000000000, 1.669200000000);
    Add(0.251100000000, 0.073900000000, 1.528100000000);
    Add(0.195360000000, 0.090980000000, 1.287640000000);
    Add(0.142100000000, 0.112600000000, 1.041900000000);
    Add(0.095640000000, 0.139020000000, 0.812950100000);
    Add(0.057950010000, 0.169300000000, 0.616200000000);
    Add(0.032010000000, 0.208020000000, 0.465180000000);
    Add(0.014700000000, 0.258600000000, 0.353300000000);
    Add(0.004900000000, 0.323000000000, 0.272000000000);
    Add(0.002400000000, 0.407300000000, 0.212300000000);
    Add(0.009300000000, 0.503000000000, 0.158200000000);
    Add(0.029100000000, 0.608200000000, 0.111700000000);
    Add(0.063270000000, 0.710000000000, 0.078249990000);
    Add(0.109600000000, 0.793200000000, 0.057250010000);
    Add(0.165500000000, 0.862000000000, 0.042160000000);
    Add(0.225749900000, 0.914850100000, 0.029840000000);
    Add(0.290400000000, 0.954000000000, 0.020300000000);
    Add(0.359700000000, 0.980300000000, 0.013400000000);
    Add(0.433449900000, 0.994950100000, 0.008749999000);
    Add(0.512050100000, 1.000000000000, 0.005749999000);
    Add(0.594500000000, 0.995000000000, 0.003900000000);
    Add(0.678400000000, 0.978600000000, 0.002749999000);
    Add(0.762100000000, 0.952000000000, 0.002100000000);
    Add(0.842500000000, 0.915400000000, 0.001800000000);
    Add(0.916300000000, 0.870000000000, 0.001650001000);
    Add(0.978600000000, 0.816300000000, 0.001400000000);
    Add(1.026300000000, 0.757000000000, 0.001100000000);
    Add(1.056700000000, 0.694900000000, 0.001000000000);
    Add(1.062200000000, 0.631000000000, 0.000800000000);
    Add(1.045600000000, 0.566800000000, 0.000600000000);
    Add(1.002600000000, 0.503000000000, 0.000340000000);
    Add(0.938400000000, 0.441200000000, 0.000240000000);
    Add(0.854449900000, 0.381000000000, 0.000190000000);
    Add(0.751400000000, 0.321000000000, 0.000100000000);
    Add(0.642400000000, 0.265000000000, 0.000049999990);
    Add(0.541900000000, 0.217000000000, 0.000030000000);
    Add(0.447900000000, 0.175000000000, 0.000020000000);
    Add(0.360800000000, 0.138200000000, 0.000010000000);
    Add(0.283500000000, 0.107000000000, 0.000000000000);
    Add(0.218700000000, 0.081600000000, 0.000000000000);
    Add(0.164900000000, 0.061000000000, 0.000000000000);
    Add(0.121200000000, 0.044580000000, 0.000000000000);
    Add(0.087400000000, 0.032000000000, 0.000000000000);
    Add(0.063600000000, 0.023200000000, 0.000000000000);
    Add(0.046770000000, 0.017000000000, 0.000000000000);
    Add(0.032900000000, 0.011920000000, 0.000000000000);
    Add(0.022700000000, 0.008210000000, 0.000000000000);
    Add(0.015840000000, 0.005723000000, 0.000000000000);
    Add(0.011359160000, 0.004102000000, 0.000000000000);
    Add(0.008110916000, 0.002929000000, 0.000000000000);
    Add(0.005790346000, 0.002091000000, 0.000000000000);
    Add(0.004109457000, 0.001484000000, 0.000000000000);
    Add(0.002899327000, 0.001047000000, 0.000000000000);
    Add(0.002049190000, 0.000740000000, 0.000000000000);
    Add(0.001439971000, 0.000520000000, 0.000000000000);
    Add(0.000999949300, 0.000361100000, 0.000000000000);
    Add(0.000690078600, 0.000249200000, 0.000000000000);
    Add(0.000476021300, 0.000171900000, 0.000000000000);
    Add(0.000332301100, 0.000120000000, 0.000000000000);
    Add(0.000234826100, 0.000084800000, 0.000000000000);
    Add(0.000166150500, 0.000060000000, 0.000000000000);
    Add(0.000117413000, 0.000042400000, 0.000000000000);
    Add(0.000083075270, 0.000030000000, 0.000000000000);
    Add(0.000058706520, 0.000021200000, 0.000000000000);
    Add(0.000041509940, 0.000014990000, 0.000000000000);
    Add(0.000029353260, 0.000010600000, 0.000000000000);
    Add(0.000020673830, 0.000007465700, 0.000000000000);
    Add(0.000014559770, 0.000005257800, 0.000000000000);
    Add(0.000010253980, 0.000003702900, 0.000000000000);
    Add(0.000007221456, 0.000002607800, 0.000000000000);
    Add(0.000005085868, 0.000001836600, 0.000000000000);
    Add(0.000003581652, 0.000001293400, 0.000000000000);
    Add(0.000002522525, 0.000000910930, 0.000000000000);
    Add(0.000001776509, 0.000000641530, 0.000000000000);
    Add(0.000001251141, 0.000000451810, 0.000000000000);
    Add(0.000000000000, 0.000000000000, 0.000000000000);
  }

 private:
  void Add(double x_bar_sample, double y_bar_sample, double z_bar_sample) {
    x_bar_samples.push_back(x_bar_sample);
    y_bar_samples.push_back(y_bar_sample);
    z_bar_samples.push_back(z_bar_sample);
  }
};

const Tables tables = Tables();
const DimensionlessSpectrum x_bar(355.0 * nm, 835.0 * nm, tables.x_bar_samples);
const DimensionlessSpectrum y_bar(355.0 * nm, 835.0 * nm, tables.y_bar_samples);
const DimensionlessSpectrum z_bar(355.0 * nm, 835.0 * nm, tables.z_bar_samples);

}  // anonymous namespace

const DimensionlessSpectrum& cie_x_bar_function() { return x_bar; }
const DimensionlessSpectrum& cie_y_bar_function() { return y_bar; }
const DimensionlessSpectrum& cie_z_bar_function() { return z_bar; }