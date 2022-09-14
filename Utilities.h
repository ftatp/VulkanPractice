#pragma once

// Indices of queue families' location
struct QueueFamilyIndices {
    int graphicsFamily = -1;                // Location of Graphics Queue family
    
    // Check if Queue family valid
    bool isValid(){
        return graphicsFamily >= 0;
    }
};