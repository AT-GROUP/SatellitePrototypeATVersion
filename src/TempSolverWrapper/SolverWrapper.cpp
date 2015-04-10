#include "SolverWrapper.h"
#include <msclr/auto_gcroot.h>

using namespace System::Runtime::InteropServices;
using namespace System;

#ifdef WRAPPER_LIB

template<class T> msclr::auto_gcroot<T^>& ManagedHolder<T>::object()
{
	return m_pObject;
}

#endif

SolverWrapper::SolverWrapper()
{
	createManagedInstances();
}

SolverWrapper::~SolverWrapper()
{
	
}

void SolverWrapper::createManagedInstances()
{
	//pATReasonerHolder = new ManagedHolder<SolverXLib::SolverX>();
	pTemporalReasonerHolder = new ManagedHolder<MProgram::TemporalReasonerX>();
	pIMHolder = new ManagedHolder<ModelLib::Model>();
}

void SolverWrapper::configurate()
{
	const std::string senderName = "Wrapper";
	const std::string sendingMessage = "<config><FileName>C:\TKBnewforAT.xml</FileName></config>";
	String^ s_senderName = gcnew String(senderName.c_str());
	String^ s_sendingMessage = gcnew String(sendingMessage.c_str());
	pIMHolder->m_pObject->configurate();
	pTemporalReasonerHolder->m_pObject->Configurate(1);
	//pATReasonerHolder->m_pObject->Configurate(s_sendingMessage);
}
void SolverWrapper::processModelTact()
{
	const std::string senderName = "Wrapper";
	const std::string sendingMessage = "aaa";
	String^ s_senderName = gcnew String(senderName.c_str());
	String^ s_sendingMessage = gcnew String(sendingMessage.c_str());
	pIMHolder->m_pObject->processNextTact(s_sendingMessage);
}
void SolverWrapper::processSolversTact()
{
	const std::string senderName = "ESKernel";
	const std::string sendingMessage = "TSolve";
	String^ s_senderName = gcnew String(senderName.c_str());
	String^ s_sendingMessage = gcnew String(sendingMessage.c_str());
	pTemporalReasonerHolder->m_pObject->ProcessMessage(s_senderName, s_sendingMessage);
//	System::Object^ OLE = gcnew System::Object();
//	pATReasonerHolder->m_pObject->ProcessMessage(s_senderName, s_sendingMessage);
}

void SolverWrapper::test()
{
	const std::string sendingMessage = "5";
	String^ s_sendingMessage = gcnew String(sendingMessage.c_str());
	//pIMHolder->m_pObject->processNextTact(s_sendingMessage);
}