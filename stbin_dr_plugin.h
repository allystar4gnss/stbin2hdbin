/*****************************************************************************
   FILE:          waas_plugin.h
   PROJECT:       STA2062 GPS application
   SW PACKAGE:    STA2062 GPS library and application
------------------------------------------------------------------------------
   DESCRIPTION:   The main application to run and test STA2062 GPS library
------------------------------------------------------------------------------
   COPYRIGHT:     (c) 2014 STMicroelectronics
------------------------------------------------------------------------------
   Created by : Michel Susini
           on : W421
*****************************************************************************/

#ifndef STBIN_DR_PLUGIN
#define STBIN_DR_PLUGIN

/*****************************************************************************
   includes
*****************************************************************************/

#include "stbin.h"
#include "dr_plugin.h"

/*****************************************************************************
   defines and macros (scope: module-local)
*****************************************************************************/

/*****************************************************************************
   typedefs and structures (scope: module-local)
*****************************************************************************/

/*****************************************************************************
   exported variables
*****************************************************************************/

/*****************************************************************************
   exported function prototypes
*****************************************************************************/

extern void             stbin_dr_plugin_init              ( dr_plugin_handler_t *handler);
extern stbin_status_t   stbin_dr_plugin_cmdif_parse       ( tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms);
extern void             stbin_dr_plugin_outmsg_transmit   ( const tU32 *msg_list, const stbin_outProcess_input *in);

#endif // __STBIN_DR_PLUGIN__
