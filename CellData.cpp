/*
 * CellData.h
 *
 *  Created on: Nov 9, 2021
 *      Author: student
 */

#include <iostream>
#include <string>
#include <sstream>
#include "CellData.h"

using namespace std;

CellData::CellData() : id("-1"), fov(-1), volume(-1), 
                        center_x(-1), center_y(-1), 
                        min_x(-1), max_x(-1), 
                        min_y(-1), max_y(-1) {}

//initialize everything

CellData::CellData(std::string id, int fov, double volume, 
                    double center_x, double center_y, 
                    double min_x, double max_x, 
                    double min_y, double max_y) : id(id), fov(fov), volume(volume),
                                                center_x(center_x), center_y(center_y), 
                                                min_x(min_x), max_x(max_x), 
                                                min_y(min_y), max_y(max_y) {}
 //initialize everything


CellData::~CellData() {} // You should not need to implement this

// bool isOneLessThanTwo(string id1, string id2) {
//     if (id1.size() < id2.size()) {
//         return true;
//     }
//     else if (id1.size() == id2.size()) {
//         for (unsigned int i = 0; i < id1.size(); ++i) {
//             if (int(id1[i]) < int(id2[i])) {
//                 return true;
//             }
//             else if (int(id1[i]) > int(id2[i])) {
//                 return false;
//             }
//         }
//     }
//     return false;
// }
bool isOneLessThanTwo(string id1, string id2) {
    size_t size1 = id1.size(), size2 = id2.size(), sizeM;
    sizeM = (size1 < size2) ? size1 : size2;
    for (size_t i = 0; i < sizeM; ++i) {
        if (int(id1[i]) < int(id2[i])) {
            return true;
        }
        else if (int(id1[i]) > int(id2[i])) {
            return false;
        }
    }
    if (size1 < size2) {
        return true;
    }
    return false;
}

bool CellData::operator<(const CellData& b) {
	// Implement this
    int lhsFov = this->fov;
    int rhsFov = b.fov;
    if (lhsFov < rhsFov) {
        return true;
    }
    else if (this->fov == b.fov) {
        if (isOneLessThanTwo(this->id,b.id)) {
            return true;
        }
    }
    return false;
}

bool CellData::operator==(const CellData& b) {
    // Implement this
    if (
        this->id == b.id &&
        this->fov == b.fov &&
        this->volume == b.volume &&
        this->center_x == b.center_x &&
        this->center_y == b.center_y &&
        this->min_x == b.min_x &&
        this->min_y == b.min_y &&
        this->max_x == b.max_x &&
        this->max_y == b.max_y
        ) {
            return true;
        }
    return false;
}

