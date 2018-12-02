/*
*	File:		Gatelinked.cpp
*	
*	Version:	1.0
* 
*	Created:	11/29/18
*	
*	Copyright:  Copyright � 2018 Airwindows, All Rights Reserved
* 
*	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc. ("Apple") in 
*				consideration of your agreement to the following terms, and your use, installation, modification 
*				or redistribution of this Apple software constitutes acceptance of these terms.  If you do 
*				not agree with these terms, please do not use, install, modify or redistribute this Apple 
*				software.
*
*				In consideration of your agreement to abide by the following terms, and subject to these terms, 
*				Apple grants you a personal, non-exclusive license, under Apple's copyrights in this 
*				original Apple software (the "Apple Software"), to use, reproduce, modify and redistribute the 
*				Apple Software, with or without modifications, in source and/or binary forms; provided that if you 
*				redistribute the Apple Software in its entirety and without modifications, you must retain this 
*				notice and the following text and disclaimers in all such redistributions of the Apple Software. 
*				Neither the name, trademarks, service marks or logos of Apple Computer, Inc. may be used to 
*				endorse or promote products derived from the Apple Software without specific prior written 
*				permission from Apple.  Except as expressly stated in this notice, no other rights or 
*				licenses, express or implied, are granted by Apple herein, including but not limited to any 
*				patent rights that may be infringed by your derivative works or by other works in which the 
*				Apple Software may be incorporated.
*
*				The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO WARRANTIES, EXPRESS OR 
*				IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY 
*				AND FITNESS FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE 
*				OR IN COMBINATION WITH YOUR PRODUCTS.
*
*				IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR CONSEQUENTIAL 
*				DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
*				OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, 
*				REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER 
*				UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN 
*				IF APPLE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
/*=============================================================================
	Gatelinked.cpp
	
=============================================================================*/
#include "Gatelinked.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

COMPONENT_ENTRY(Gatelinked)


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Gatelinked::Gatelinked
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Gatelinked::Gatelinked(AudioUnit component)
	: AUEffectBase(component)
{
	CreateElements();
	Globals()->UseIndexedParameters(kNumberOfParameters);
	SetParameter(kParam_One, kDefaultValue_ParamOne );
	SetParameter(kParam_Two, kDefaultValue_ParamTwo );
	SetParameter(kParam_Three, kDefaultValue_ParamThree );
	SetParameter(kParam_Four, kDefaultValue_ParamFour );
	SetParameter(kParam_Five, kDefaultValue_ParamFive );
         
#if AU_DEBUG_DISPATCHER
	mDebugDispatcher = new AUDebugDispatcher (this);
#endif
	
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Gatelinked::GetParameterValueStrings
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult			Gatelinked::GetParameterValueStrings(AudioUnitScope		inScope,
                                                                AudioUnitParameterID	inParameterID,
                                                                CFArrayRef *		outStrings)
{
        
    return kAudioUnitErr_InvalidProperty;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Gatelinked::GetParameterInfo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult			Gatelinked::GetParameterInfo(AudioUnitScope		inScope,
                                                        AudioUnitParameterID	inParameterID,
                                                        AudioUnitParameterInfo	&outParameterInfo )
{
	ComponentResult result = noErr;

	outParameterInfo.flags = 	kAudioUnitParameterFlag_IsWritable
						|		kAudioUnitParameterFlag_IsReadable;
    
    if (inScope == kAudioUnitScope_Global) {
        switch(inParameterID)
        {
           case kParam_One:
                AUBase::FillInParameterName (outParameterInfo, kParameterOneName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamOne;
                break;
            case kParam_Two:
                AUBase::FillInParameterName (outParameterInfo, kParameterTwoName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamTwo;
                break;
            case kParam_Three:
                AUBase::FillInParameterName (outParameterInfo, kParameterThreeName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamThree;
                break;
           case kParam_Four:
                AUBase::FillInParameterName (outParameterInfo, kParameterFourName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamFour;
                break;
           case kParam_Five:
                AUBase::FillInParameterName (outParameterInfo, kParameterFiveName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamFive;
                break;
           default:
                result = kAudioUnitErr_InvalidParameter;
                break;
            }
	} else {
        result = kAudioUnitErr_InvalidParameter;
    }
    


	return result;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Gatelinked::GetPropertyInfo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult			Gatelinked::GetPropertyInfo (AudioUnitPropertyID	inID,
                                                        AudioUnitScope		inScope,
                                                        AudioUnitElement	inElement,
                                                        UInt32 &		outDataSize,
                                                        Boolean &		outWritable)
{
	return AUEffectBase::GetPropertyInfo (inID, inScope, inElement, outDataSize, outWritable);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// state that plugin supports only stereo-in/stereo-out processing
UInt32 Gatelinked::SupportedNumChannels(const AUChannelInfo ** outInfo)
{
	if (outInfo != NULL)
	{
		static AUChannelInfo info;
		info.inChannels = 2;
		info.outChannels = 2;
		*outInfo = &info;
	}

	return 1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Gatelinked::GetProperty
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult			Gatelinked::GetProperty(	AudioUnitPropertyID inID,
                                                        AudioUnitScope 		inScope,
                                                        AudioUnitElement 	inElement,
                                                        void *			outData )
{
	return AUEffectBase::GetProperty (inID, inScope, inElement, outData);
}

//	Gatelinked::Initialize
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult Gatelinked::Initialize()
{
    ComponentResult result = AUEffectBase::Initialize();
    if (result == noErr)
        Reset(kAudioUnitScope_Global, 0);
    return result;
}

#pragma mark ____GatelinkedEffectKernel



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Gatelinked::GatelinkedKernel::Reset()
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult		Gatelinked::Reset(AudioUnitScope inScope, AudioUnitElement inElement)
{
	iirLowpassAL = 0.0;
	iirLowpassBL = 0.0;
	iirHighpassAL = 0.0;
	iirHighpassBL = 0.0;
	iirLowpassAR = 0.0;
	iirLowpassBR = 0.0;
	iirHighpassAR = 0.0;
	iirHighpassBR = 0.0;
	treblefreq = 1.0;
	bassfreq = 0.0;
	flip = false;
	fpNShapeL = 0.0;
	fpNShapeR = 0.0;
	return noErr;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Gatelinked::ProcessBufferLists
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
OSStatus		Gatelinked::ProcessBufferLists(AudioUnitRenderActionFlags & ioActionFlags,
													const AudioBufferList & inBuffer,
                                                    AudioBufferList & outBuffer,
                                                    UInt32 			inFramesToProcess)
{
	Float32 * inputL = (Float32*)(inBuffer.mBuffers[0].mData);
	Float32 * inputR = (Float32*)(inBuffer.mBuffers[1].mData);
	Float32 * outputL = (Float32*)(outBuffer.mBuffers[0].mData);
	Float32 * outputR = (Float32*)(outBuffer.mBuffers[1].mData);
	UInt32 nSampleFrames = inFramesToProcess;
	long double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= GetSampleRate();
	//speed settings around release
	Float64 threshold = pow(GetParameter( kParam_One ),2);
	//gain settings around threshold
	Float64 trebledecay = pow(1.0-GetParameter( kParam_Two ),2)/4196.0;
	Float64 bassdecay =  pow(1.0-GetParameter( kParam_Three ),2)/8192.0;
	Float64 slowAttack = (pow(GetParameter( kParam_Four ),3)*3)+0.003;
	Float64 wet = GetParameter( kParam_Five );
	slowAttack /= overallscale;
	trebledecay /= overallscale;
	bassdecay /= overallscale;
	trebledecay += 1.0;
	bassdecay += 1.0;
	Float64 attackSpeed;
	Float64 highestSample;

	while (nSampleFrames-- > 0) {
		long double inputSampleL = *inputL;
		long double inputSampleR = *inputR;
		static int noisesourceL = 0;
		static int noisesourceR = 850010;
		int residue;
		double applyresidue;
		
		noisesourceL = noisesourceL % 1700021; noisesourceL++;
		residue = noisesourceL * noisesourceL;
		residue = residue % 170003; residue *= residue;
		residue = residue % 17011; residue *= residue;
		residue = residue % 1709; residue *= residue;
		residue = residue % 173; residue *= residue;
		residue = residue % 17;
		applyresidue = residue;
		applyresidue *= 0.00000001;
		applyresidue *= 0.00000001;
		inputSampleL += applyresidue;
		if (inputSampleL<1.2e-38 && -inputSampleL<1.2e-38) {
			inputSampleL -= applyresidue;
		}
		
		noisesourceR = noisesourceR % 1700021; noisesourceR++;
		residue = noisesourceR * noisesourceR;
		residue = residue % 170003; residue *= residue;
		residue = residue % 17011; residue *= residue;
		residue = residue % 1709; residue *= residue;
		residue = residue % 173; residue *= residue;
		residue = residue % 17;
		applyresidue = residue;
		applyresidue *= 0.00000001;
		applyresidue *= 0.00000001;
		inputSampleR += applyresidue;
		if (inputSampleR<1.2e-38 && -inputSampleR<1.2e-38) {
			inputSampleR -= applyresidue;
		}
		//for live air, we always apply the dither noise. Then, if our result is 
		//effectively digital black, we'll subtract it again. We want a 'air' hiss
		double drySampleL = inputSampleL;
		double drySampleR = inputSampleR;
		
		if (fabs(inputSampleL) > fabs(inputSampleR)) {
			attackSpeed = slowAttack - (fabs(inputSampleL)*slowAttack*0.5);
			highestSample = fabs(inputSampleL);
		} else {
			attackSpeed = slowAttack - (fabs(inputSampleR)*slowAttack*0.5); //we're triggering off the highest amplitude
			highestSample = fabs(inputSampleR); //and making highestSample the abs() of that amplitude
		}
		
		if (attackSpeed < 0.0) attackSpeed = 0.0;
		//softening onset click depending on how hard we're getting it
		
		if (flip)
		{
			if (highestSample > threshold)
			{
				treblefreq += attackSpeed;
				if (treblefreq > 1.0) treblefreq = 1.0;
				bassfreq -= attackSpeed;
				bassfreq -= attackSpeed;
				if (bassfreq < 0.0) bassfreq = 0.0;
				iirLowpassAL = iirLowpassBL = inputSampleL;
				iirHighpassAL = iirHighpassBL = 0.0;
				iirLowpassAR = iirLowpassBR = inputSampleR;
				iirHighpassAR = iirHighpassBR = 0.0;
			}
			else
			{
				treblefreq -= bassfreq;
				treblefreq /= trebledecay;
				treblefreq += bassfreq;
				bassfreq -= treblefreq;
				bassfreq /= bassdecay;
				bassfreq += treblefreq;
			}
			
			if (treblefreq >= 1.0) {
				iirLowpassAL = inputSampleL;
				iirLowpassAR = inputSampleR;
			} else {
				iirLowpassAL = (iirLowpassAL * (1.0 - treblefreq)) + (inputSampleL * treblefreq);
				iirLowpassAR = (iirLowpassAR * (1.0 - treblefreq)) + (inputSampleR * treblefreq);
			}
			
			if (bassfreq > 0.0) {
				iirHighpassAL = (iirHighpassAL * (1.0 - bassfreq)) + (inputSampleL * bassfreq);
				iirHighpassAR = (iirHighpassAR * (1.0 - bassfreq)) + (inputSampleR * bassfreq);
			} else {
				iirHighpassAL = 0.0;
				iirHighpassAR = 0.0;
			}
			
			if (treblefreq > bassfreq) {
				inputSampleL = (iirLowpassAL - iirHighpassAL);
				inputSampleR = (iirLowpassAR - iirHighpassAR);
			} else {
				inputSampleL = 0.0;
				inputSampleR = 0.0;
			}
		}
		else
		{
			if (highestSample > threshold)
			{
				treblefreq += attackSpeed;
				if (treblefreq > 1.0) treblefreq = 1.0;
				bassfreq -= attackSpeed;
				bassfreq -= attackSpeed;
				if (bassfreq < 0.0) bassfreq = 0.0;
				iirLowpassAL = iirLowpassBL = inputSampleL;
				iirHighpassAL = iirHighpassBL = 0.0;
				iirLowpassAR = iirLowpassBR = inputSampleR;
				iirHighpassAR = iirHighpassBR = 0.0;
			}
			else
			{
				treblefreq -= bassfreq;
				treblefreq /= trebledecay;
				treblefreq += bassfreq;
				bassfreq -= treblefreq;
				bassfreq /= bassdecay;
				bassfreq += treblefreq;
			}
			
			if (treblefreq >= 1.0) {
				iirLowpassBL = inputSampleL;
				iirLowpassBR = inputSampleR;
			} else {
				iirLowpassBL = (iirLowpassBL * (1.0 - treblefreq)) + (inputSampleL * treblefreq);
				iirLowpassBR = (iirLowpassBR * (1.0 - treblefreq)) + (inputSampleR * treblefreq);
			}
			
			if (bassfreq > 0.0) {
				iirHighpassBL = (iirHighpassBL * (1.0 - bassfreq)) + (inputSampleL * bassfreq);
				iirHighpassBR = (iirHighpassBR * (1.0 - bassfreq)) + (inputSampleR * bassfreq);
			} else {
				iirHighpassBL = 0.0;
				iirHighpassBR = 0.0;
			}
			
			if (treblefreq > bassfreq) {
				inputSampleL = (iirLowpassBL - iirHighpassBL);
				inputSampleR = (iirLowpassBR - iirHighpassBR);
			} else {
				inputSampleL = 0.0;
				inputSampleR = 0.0;
			}			
		}
		//done full gated envelope filtered effect
		inputSampleL  = ((1-wet)*drySampleL)+(wet*inputSampleL);
		inputSampleR  = ((1-wet)*drySampleR)+(wet*inputSampleR);
		//we're going to set up a dry/wet control instead of a min. threshold
		
		flip = !flip;
				
		//noise shaping to 32-bit floating point
		Float32 fpTemp = inputSampleL;
		fpNShapeL += (inputSampleL-fpTemp);
		inputSampleL += fpNShapeL;
		//if this confuses you look at the wordlength for fpTemp :)
		fpTemp = inputSampleR;
		fpNShapeR += (inputSampleR-fpTemp);
		inputSampleR += fpNShapeR;
		//for deeper space and warmth, we try a non-oscillating noise shaping
		//that is kind of ruthless: it will forever retain the rounding errors
		//except we'll dial it back a hair at the end of every buffer processed
		//end noise shaping on 32 bit output
		
		*outputL = inputSampleL;
		*outputR = inputSampleR;
		//direct stereo out
		
		inputL += 1;
		inputR += 1;
		outputL += 1;
		outputR += 1;
	}
	fpNShapeL *= 0.999999;
	fpNShapeR *= 0.999999;
	//we will just delicately dial back the FP noise shaping, not even every sample
	//this is a good place to put subtle 'no runaway' calculations, though bear in mind
	//that it will be called more often when you use shorter sample buffers in the DAW.
	//So, very low latency operation will call these calculations more often.	
	return noErr;
}

