/*
 *
 *  Copyright (c) 2012-2015 VMware, Inc.  All Rights Reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not
 *  use this file except in compliance with the License.  You may obtain a copy
 *  of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, without
 *  warranties or conditions of any kind, EITHER EXPRESS OR IMPLIED.  See the
 *  License for the specific language governing permissions and limitations
 *  under the License.
 *
 */

package com.vmware.identity.idm.server.performance;

import java.util.LinkedList;
import java.util.List;

import com.vmware.identity.diagnostics.DiagnosticsLoggerFactory;
import com.vmware.identity.diagnostics.IDiagnosticsLogger;
import com.vmware.identity.idm.server.config.IdmServerConfig;
import com.vmware.identity.idm.server.provider.ldap.LdapWithAdMappingsProvider;
import com.vmware.identity.performanceSupport.ILdapQueryStat;
import com.vmware.identity.performanceSupport.IdmAuthStat;
import com.vmware.identity.performanceSupport.IIdmAuthStat.ActivityKind;

public class IdmAuthStatRecorder implements IIdmAuthStatRecorder {
    private static final IDiagnosticsLogger logger = DiagnosticsLoggerFactory.getLogger(IdmAuthStatRecorder.class);
    private boolean _summarizeLdapQueries;
    private String _tenantName;
    private String _providerType;
    private String _providerName;
    private int _providerFlag;
    private ActivityKind _opType;
    private String _upn;
    private long _startTime;
    private List<ILdapQueryStat> _ldapQueries;

    public IdmAuthStatRecorder(String tenantName, String providerType,
            String providerName, int providerFlag, ActivityKind opType,
            String upn, boolean summarizeLdapQueries) {
        this._summarizeLdapQueries = summarizeLdapQueries;
        this._tenantName = tenantName;
        this._providerType = providerType;
        this._providerName = providerName;
        this._providerFlag = providerFlag;
        this._opType = opType;
        this._upn = upn;
        this._ldapQueries = new LinkedList<ILdapQueryStat>();
    }

    @Override
    public void start() {
        this._startTime = System.currentTimeMillis();
    }

    @Override
    public void add(List<ILdapQueryStat> ldapQueries) {
        if (ldapQueries != null) {
            this._ldapQueries.addAll(ldapQueries);
        }
    }

    @Override
    public void add(ILdapQueryStat ldapQuery) {
        if (ldapQuery != null) {
            this._ldapQueries.add(ldapQuery);
        }
    }

    @Override
    public void end() {
        try {
            IdmAuthStat authStat = new IdmAuthStat(this._providerType,
                    this._providerName, this._providerFlag, this._opType,
                    this._upn, this._startTime, System.currentTimeMillis()
                            - this._startTime, this._ldapQueries);

            PerformanceMonitor.getInstance().getCache(this._tenantName)
                    .add(authStat);
        } catch (Exception ex) {
            logger.warn(String.format("Failed to log IdmAuthStat for tenant: %s, Ignored.", this._tenantName), ex);
        }
    }

    @Override
    public boolean summarizeLdapQueries(){
        return this._summarizeLdapQueries;
    }
}
