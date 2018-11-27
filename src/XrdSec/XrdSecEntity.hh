#ifndef __SEC_ENTITY_H__
#define __SEC_ENTITY_H__
/******************************************************************************/
/*                                                                            */
/*                       X r d S e c E n t i t y . h h                        */
/*                                                                            */
/* (c) 2005 by the Board of Trustees of the Leland Stanford, Jr., University  */
/*   Produced by Andrew Hanushevsky for Stanford University under contract    */
/*              DE-AC02-76-SFO0515 with the Department of Energy              */
/*                                                                            */
/* This file is part of the XRootD software suite.                            */
/*                                                                            */
/* XRootD is free software: you can redistribute it and/or modify it under    */
/* the terms of the GNU Lesser General Public License as published by the     */
/* Free Software Foundation, either version 3 of the License, or (at your     */
/* option) any later version.                                                 */
/*                                                                            */
/* XRootD is distributed in the hope that it will be useful, but WITHOUT      */
/* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or      */
/* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public       */
/* License for more details.                                                  */
/*                                                                            */
/* You should have received a copy of the GNU Lesser General Public License   */
/* along with XRootD in a file called COPYING.LESSER (LGPL license) and file  */
/* COPYING (GPL license).  If not, see <http://www.gnu.org/licenses/>.        */
/*                                                                            */
/* The copyright holder's institutional names and contributor's names may not */
/* be used to endorse or promote products derived from this software without  */
/* specific prior written permission of the institution or contributor.       */
/******************************************************************************/

//------------------------------------------------------------------------------
//! This object is returned during authentication. This is most relevant for
//! client authentication unless mutual authentication has been implemented
//! in which case the client can also authenticate the server. It is embeded
//! in each protocol object to facilitate mutual authentication. Note that the
//! destructor does nothing and it is the responsibility of the protocol object
//! to delete the XrdSecEntity data members, if need be.
//!
//! Note: The host member contents are depdent on the dnr/nodnr setting and
//!       and contain a host name or an IP address. To get the real host name
//!       use addrInfo->Name(), this is required for any hostname comparisons.
//------------------------------------------------------------------------------

#include <string.h>
#include <sys/types.h>

#define XrdSecPROTOIDSIZE 8

class  XrdNetAddrInfo;

class  XrdSecEntity
{
public:
         char   prot[XrdSecPROTOIDSIZE];  // Protocol used
         char   *name;                    // Entity's name
         char   *host;                    // Entity's host name dnr dependent
         char   *vorg;                    // Entity's virtual organization
         char   *role;                    // Entity's role
         char   *grps;                    // Entity's group names
         char   *endorsements;            // Protocol specific endorsements
         char   *moninfo;                 // Additional information for monitoring 
         char   *creds;                   // Raw client credentials or certificate
         int     credslen;                // Length of the 'creds' field
         int     rsvd;                    // Reserved field
XrdNetAddrInfo  *addrInfo;                // Connection details from getProtocol
const    char   *tident;                  // Trace identifier always preset
         void   *sessvar;                 // Plugin settable storage pointer
                                          // that is common to the session. Free
                                          // it in your XrdSfsFileSystem::Disc()
                                          // implementation, as needed.
         uid_t   uid;                     // Unix uid or 0 if none
         gid_t   gid;                     // Unix gid or 0 if none
         void   *future[3];               // Reserved for future expansion

         XrdSecEntity(const char *pName = "")
                     {Reset();
                      strncpy(prot, pName, XrdSecPROTOIDSIZE-1);
                      prot[XrdSecPROTOIDSIZE-1] = '\0';
                     }
        ~XrdSecEntity() {}

         void Reset()
              {
               memset( prot, 0, XrdSecPROTOIDSIZE );
               name = 0;
               host = 0;
               vorg = 0;
               role = 0;
               grps = 0;
               endorsements = 0;
               moninfo = 0;
               creds = 0;
               credslen = 0;
               rsvd = 0;
               addrInfo = 0;
               tident = 0;
               sessvar = 0;
               uid     = 0;
               gid     = 0;
               memset(future, 0, sizeof(future));
             }
};

#define XrdSecClientName XrdSecEntity
#define XrdSecServerName XrdSecEntity
#endif
