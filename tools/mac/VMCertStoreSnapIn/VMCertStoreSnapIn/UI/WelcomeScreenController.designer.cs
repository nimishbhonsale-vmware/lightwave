// WARNING
//
// This file has been generated automatically by Xamarin Studio to store outlets and
// actions made in the UI designer. If it is removed, they will be lost.
// Manual changes to this file may not be handled correctly.
//
using Foundation;
using System.CodeDom.Compiler;

namespace VMCertStoreSnapIn
{
	[Register ("WelcomeScreenController")]
	partial class WelcomeScreenController
	{
		[Outlet]
		AppKit.NSPopUpButton ConnectPopupButton { get; set; }

		[Action ("LoginAction:")]
		partial void LoginAction (Foundation.NSObject sender);

		[Action ("OnConnect:")]
		partial void OnConnect (Foundation.NSObject sender);
		
		void ReleaseDesignerOutlets ()
		{
			if (ConnectPopupButton != null) {
				ConnectPopupButton.Dispose ();
				ConnectPopupButton = null;
			}
		}
	}
}
