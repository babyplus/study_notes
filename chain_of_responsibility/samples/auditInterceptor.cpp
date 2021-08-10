#include "auditInterceptor.h"

AuditInterceptor::AuditInterceptor()
{
    TRACK("begin");
}

AuditInterceptor::~AuditInterceptor()
{
    TRACK("end");
}

bool AuditInterceptor::process(Action* action)
{
    TRACK();
}
