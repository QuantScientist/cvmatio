/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2009, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "MatlabIO.hpp"

bool MatlabIO::open(string filename, string mode) {

    // open the file
    if (mode.compare("-r") != 0 || mode.compare("-w") != 0) return false;
    fid_ = fopen(filename.c_str(), mode.c_str);
    if (!fid_) return false;
    else return true;
}

bool close(void) {

    // close the file and release any associated objects
    int err = fclose(fid_);
    fid_ = NULL;
    if (err) return false;
    else return true;
}


void MatlabIO::getHeader(void) {
    // get the header information from the Mat file
    for (int n = 0; n < HEADER_LENGTH+1; ++n) header_[n] = '\0';
    fread(header_,  sizeof(char), HEADER_LENGTH,  fid_);
    fread(subsys_,  sizeof(char), SUBSYS_LENGTH,  fid_);
    fread(&version_, sizeof(int16_t), VERSION_LENGTH, fid_);
    fread(&endian_,  sizeof(int16_t), ENDIAN_LENGTH,  fid_);
}


MatlabIOContainer MatlabIO::readVariable(void) {

    // get the data type and number of bytes consumed
    // by this variable
    int data_type;
    int nbytes;
    fread(&data_type, sizeof(int), 1, fid_);
    fread(&nbytes,    sizeof(int), 1, fid_);

    // read the binary data block
    char * data = new char[nbytes];
    fread(data, sizeof(char), nbytes, fid_);

    MatlabIOContainer variable;
    return variable;
}

std::vector<MatlabIOContainer> MatlabIO::read(void) {

    // allocate the output
    std::vector<MatlabIOContainer> variables;
    return variables;
}
