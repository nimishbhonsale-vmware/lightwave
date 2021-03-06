﻿/*
 * Copyright © 2012-2015 VMware, Inc.  All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the “License”); you may not
 * use this file except in compliance with the License.  You may obtain a copy
 * of the License at http://www.apache.org/licenses/LICENSE-2.0
 *·
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an “AS IS” BASIS, without
 * warranties or conditions of any kind, EITHER EXPRESS OR IMPLIED.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

using System;

namespace VMCA.Client
{
    public class VMCAException : Exception
    {
        public UInt32 OriginalErrorCode { get; protected set; }

        public VMCAErrorCode ErrorCode { get { return (VMCAErrorCode)OriginalErrorCode; } }

        public override string Message {
            get {
                return string.Format ("Error Number: {0}, Error Name: {1}, Error String: {2}", OriginalErrorCode, ErrorCode.ToString (), base.Message);
            }
        }

        public VMCAException (UInt32 errorCode, string error) : base (error)
        {
            OriginalErrorCode = errorCode;
        }
    }
}
