/*
 * Super Entity Game Server
 * http://segs.sf.net/
 * Copyright (c) 2006 Super Entity Game Server Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 *
 * $Id: MapServerInterface.h 305 2007-01-21 08:53:16Z nemerle $
 */

// Inclusion guards
#pragma once
#ifndef MAPSERVERINTERFACE_H
#define MAPSERVERINTERFACE_H

#include <ace/INET_Addr.h>
#include <string>
#include "Base.h"
#include "RoamingServer.h"
class MapServer;
// this is a proxy for calling GameServer services
class IMapServer : public RoamingServer
{
public:
	virtual u32 ExpectClient(const ACE_INET_Addr &from,u64 id,u16 access_level)=0;
	virtual void AssociatePlayerWithMap(u64 player_id,int map_number)=0;
	virtual bool ShutDown(const std::string &reason)=0;
	virtual bool Online()=0;
	virtual const ACE_INET_Addr &getAddress()=0;
};
class MapServerInterface : public Server
{
public:
	MapServerInterface(IMapServer *mi) : m_instance(mi){};
	~MapServerInterface(void){};
	u32 ExpectClient(const ACE_INET_Addr &from,u64 id,u16 access_level);
	void AssociatePlayerWithMap(u64 player_id,int map_number);

	bool ReadConfig(const std::string &name); // later name will be used to read GameServer specific configuration
	bool Run(void);
	bool ShutDown(const std::string &reason);
	bool isLocal(){return true;} // this method returns true if this interface is a local ( same process )
	bool Online();
	const ACE_INET_Addr &getAddress();

protected:
	IMapServer *m_instance;
};

#endif // MAPSERVERINTERFACE_H
