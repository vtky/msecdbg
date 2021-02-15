//
// taint.h
//
// Taint Tracking Definitions, Data Declarations, and Function Headers for the !expoitable Crash Analyzer
//
//
// Developed by the Microsoft Security Engineering Center (MSEC)
// Copyright 2008-2013, Microsoft Corporation
//
//	Microsoft Public License (Ms-PL)
//	This license governs use of the accompanying software. If you use the software, you accept this license. If you do not accept the license, do not use the software.
//
//	Definitions
//		The terms "reproduce," "reproduction," "derivative works," and "distribution" have the same meaning here as under U.S. copyright law. A "contribution" is the original software, or any additions or changes to the software. A "contributor" is any person that distributes its contribution under this license. "Licensed patents" are a contributor's patent claims that read directly on its contribution.
//	Grant of Rights
//		(A) Copyright Grant- Subject to the terms of this license, including the license conditions and limitations in section 3, each contributor grants you a non-exclusive, worldwide, royalty-free copyright license to reproduce its contribution, prepare derivative works of its contribution, and distribute its contribution or any derivative works that you create.
//		(B) Patent Grant- Subject to the terms of this license, including the license conditions and limitations in section 3, each contributor grants you a non-exclusive, worldwide, royalty-free license under its licensed patents to make, have made, use, sell, offer for sale, import, and/or otherwise dispose of its contribution in the software or derivative works of the contribution in the software.
//	Conditions and Limitations
//		(A) No Trademark License- This license does not grant you rights to use any contributors' name, logo, or trademarks. 
//		(B) If you bring a patent claim against any contributor over patents that you claim are infringed by the software, your patent license from such contributor to the software ends automatically. 
//		(C) If you distribute any portion of the software, you must retain all copyright, patent, trademark, and attribution notices that are present in the software. 
//		(D) If you distribute any portion of the software in source code form, you may do so only under this license by including a complete copy of this license with your distribution. If you distribute any portion of the software in compiled or object code form, you may only do so under a license that complies with this license. 
//		(E) The software is licensed "as-is." You bear the risk of using it. The contributors give no express warranties, guarantees, or conditions. You may have additional consumer rights under your local laws which this license cannot change. To the extent permitted under your local laws, the contributors exclude the implied warranties of merchantability, fitness for a particular purpose and non-infringement.
//


#pragma once

#include "exploitable.h"
#include <stack>

#ifdef TAINT_MODULE

///
// Internal Classes
///
class StackEmulator
{
public:
	StackEmulator()
	{
		dwVirtualStackTaintCount = 0;
	}

	bool Pop()
	{
		bool fResult = false;

		if( !IsEmpty() )
		{
			fResult = stkVirtualStack.top();

			stkVirtualStack.pop();

			if( fResult )
			{
				dwVirtualStackTaintCount -= 1;
			}
		}

		return( fResult );
	}

	void Push( const OPERAND_SET& setCalculationRegisters, const OPERAND_SET& setExpandedTaintedRegisters )
	{
		bool fIsTainted = false;
		
		for( OPERAND_SET::const_iterator itOperand = setCalculationRegisters.begin(); !fIsTainted && (itOperand != setCalculationRegisters.end()); itOperand++ )
		{
			fIsTainted = setExpandedTaintedRegisters.find( *itOperand ) != setExpandedTaintedRegisters.end();
		}

		stkVirtualStack.push( fIsTainted );

		if( fIsTainted )
		{
			dwVirtualStackTaintCount += 1;
		}
	}

	void Push( const OPERAND& objRegister, const OPERAND_SET& setExpandedTaintedRegisters )
	{
		bool fIsTainted = (setExpandedTaintedRegisters.find( objRegister ) != setExpandedTaintedRegisters.end() );

		stkVirtualStack.push( fIsTainted );

		if( fIsTainted )
		{
			dwVirtualStackTaintCount += 1;
		}
	}

	void PushConstant()
	{
		stkVirtualStack.push( false );
	}

	bool IsEmpty()
	{
		return( stkVirtualStack.empty() );
	}

	bool HasTaintedElements()
	{
		return( dwVirtualStackTaintCount != 0 );
	}

private:
	std::stack<bool> stkVirtualStack;
	DWORD dwVirtualStackTaintCount;
};

///
// Internal Functions
///

void UpdateInverseOperandSets( DWORD dwProcessor, const OPERAND &objRegister, OPERAND_SET *psetAdd, OPERAND_SET *pSetClear );

#endif

///
// Functions
///
bool AssignTaint( DWORD dwProcessor, bool fTaintInitialDestinationPointerRegisters, __in INSTRUCTION_LIST *pInstructionBlock );
