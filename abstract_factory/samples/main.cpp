#include "delete.h"
#include "greeFactory.h"
#include "greeAircondition.h"
#include "greeRemoteControl.h"
#include "mideaFactory.h"
#include "mideaAircondition.h"
#include "mideaRemoteControl.h"

int main()
{
    Factory* gree_f = new GreeFactory();
    IAircondition* gree_acd = gree_f->produce_aircondition();
    IRemoteControl* gree_rc = gree_f->produce_remote_control();
    gree_rc->bind(gree_acd);

    DELETE(gree_f);
    DELETE(gree_acd);
    DELETE(gree_rc);

    TRACK("-----------------------------------------------------");

    Factory* midea_f = new MideaFactory();
    IAircondition* midea_acd = midea_f->produce_aircondition();
    IRemoteControl* midea_rc = midea_f->produce_remote_control();
    midea_rc->bind(midea_acd);

    DELETE(midea_f);
    DELETE(midea_acd);
    DELETE(midea_rc);

    return 0;
}
