/*
GRT MIT License
Copyright (c) <2012> <Nicholas Gillian, Media Lab, MIT>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial 
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "PostProcessing.h"
namespace GRT{
    
PostProcessing::StringPostProcessingMap* PostProcessing::stringPostProcessingMap = NULL;
UINT PostProcessing::numPostProcessingInstances = 0;
    
PostProcessing* PostProcessing::createInstanceFromString(string const &postProcessingType){
    
    StringPostProcessingMap::iterator iter = getMap()->find( postProcessingType );
    if( iter == getMap()->end() ){
        return NULL;
    }
    return iter->second();
}
    
PostProcessing::PostProcessing(void){
    postProcessingType = "NOT_SET";
    postProcessingInputMode = INPUT_MODE_NOT_SET;
    postProcessingOutputMode = OUTPUT_MODE_NOT_SET;
    initialized = false; 
    numInputDimensions = 0;
    numOutputDimensions = 0;
    numPostProcessingInstances++;
}
    
PostProcessing::~PostProcessing(void){
    if( --numPostProcessingInstances == 0 ){
        delete stringPostProcessingMap;
        stringPostProcessingMap = NULL;
    }
}

bool PostProcessing::copyBaseVariables(const PostProcessing *postProcessingModule){
    
    if( postProcessingModule == NULL ){
        errorMessage = "copyBaseVariables(const PostProcessing *postProcessingModule) - postProcessingModule pointer is NULL!";
        errorLog << errorMessage << endl;
        return false;
    }
    
    if( !this->copyGRTBaseVariables( postProcessingModule ) ){
        return false;
    }
    
    this->postProcessingType = postProcessingModule->postProcessingType;
    this->postProcessingInputMode =  postProcessingModule->postProcessingInputMode;
    this->postProcessingOutputMode =  postProcessingModule->postProcessingOutputMode;
    this->initialized = postProcessingModule->initialized;
    this->numInputDimensions = postProcessingModule->numInputDimensions;
    this->numOutputDimensions = postProcessingModule->numOutputDimensions;
    this->processedData = postProcessingModule->processedData;
    this->debugLog = postProcessingModule->debugLog;
    this->errorLog = postProcessingModule->errorLog;
    this->warningLog = postProcessingModule->warningLog;
    return true;
}
    
PostProcessing* PostProcessing::createNewInstance() const{
    return createInstanceFromString(postProcessingType);
}

string PostProcessing::getPostProcessingType() const{ 
    return postProcessingType;
}
    
UINT PostProcessing::getPostProcessingInputMode() const{ 
     return postProcessingInputMode; 
}
    
UINT PostProcessing::getPostProcessingOutputMode() const{ 
    return postProcessingOutputMode; 
}
    
UINT PostProcessing::getNumInputDimensions() const{ 
    return numInputDimensions; 
}
    
UINT PostProcessing::getNumOutputDimensions() const{ 
    return numOutputDimensions; 
}
    
bool PostProcessing::getInitialized() const{ 
    return initialized; 
}
    
bool PostProcessing::getIsPostProcessingInputModePredictedClassLabel() const{ 
    return postProcessingInputMode==INPUT_MODE_PREDICTED_CLASS_LABEL; 
}
    
bool PostProcessing::getIsPostProcessingInputModeClassLikelihoods() const{ 
    return postProcessingInputMode==INPUT_MODE_CLASS_LIKELIHOODS; 
}
    
bool PostProcessing::getIsPostProcessingOutputModePredictedClassLabel() const{ 
    return postProcessingOutputMode==OUTPUT_MODE_PREDICTED_CLASS_LABEL; 
}
    
bool PostProcessing::getIsPostProcessingOutputModeClassLikelihoods() const{ 
    return postProcessingOutputMode==OUTPUT_MODE_CLASS_LIKELIHOODS; 
}
    
vector< double > PostProcessing::getProcessedData() const{ 
    return processedData; 
}

} //End of namespace GRT
