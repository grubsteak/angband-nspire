/**
 * \file AppDelegate.m
 * \brief This is a minimal implementation of the OS X front end.
 *
 * Copyright (c) 2020 Eric Branlund
 *
 * This work is free software; you can redistribute it and/or modify it
 * under the terms of either:
 *
 * a) the GNU General Public License as published by the Free Software
 *    Foundation, version 2, or
 *
 * b) the "Angband licence":
 *    This software may be copied and distributed for educational, research,
 *    and not for profit purposes provided that this copyright and statement
 *    are included in all such copies.  Other copyrights may also apply.
 *
 * Use this file to rebuild the .nib files with Xcode without having to pull
 * in all of the Angband source.  This is the procedure with Xcode 11.3:
 *
 * 1) Create a new Xcode project for a macOS App.
 * 2) You can set the "Product Name", "Team", "Organization Name",
 *    "Organization Identifier" as you wish.  Setting the product name to
 *    "angband" and the "Organization Identifier" to "org.rephial" will match
 *    the bundle identifier used in the full builds for Angband.  Set
 *    "Language" to "Objective-C" and "User Interface" to "XIB".  Leave
 *    "Create Document-Based Application" and "Use Core Data" off.
 *    The settings for "Include Unit Tests" and "Include UI Tests" don't
 *    matter; you can turn them off to avoid extra clutter.
 * 3) In the Angband project settings, set "Main Interface" to "MainMenu".
 *    Set the deployment target to what's used in Angband's Makefile.osx.
 *    When this was written, that was 10.9.
 * 4) Copy src/cocoa/AppDelegate.h, src/cocoa/AppDelegate.m,
 *    src/cocoa/TileSetScaling.h, and src/cocoa/TileSetScaling.m from the
 *    Angband source files to the directory in the project with main.m.  Copy
 *    src/cocoa/Base.lproj/MainMenu.xib and
 *    src/cocoa/Base.lproj/TileSetScaling.xib to the Base.lproj subdirectory
 *    of that directory.
 * 5) Within Xcode, add TileSetScaling.h, TileSetScaling.m, and
 *    Base.lproj/TileSetScaling.xib to the project files (use the ones copied
 *    to the Xcode project's directory).
 * 6) (This annoyance seems to have gone away between Xcode 11 and Xcode 13;
 *    leaving it here just in case) If you modify MainMenu.xib or
 *    TileSetScaling.xib after copying them over, you may want to set them so
 *    that they can be opened in older versions of Xcode.  For each one that
 *    was changed, select it in Xcode, and select one of the things, like
 *    "File's Owner" from it.  In the file information panel for it, there
 *    will be a section labeled "Document Editing" with an option menu for
 *    "Opens in".  Choosing one of the options other than "Latest Xcode"
 *    will close the file and save it with the appropriate flags.  Note
 *    that reopening the .xib file in Xcode and saving it will cause the
 *    version to revert to the latest Xcode.
 * 7) Use Xcode's Product->Build For->Running menu entry to build the project.
 * 8) The generated .nib files will be in
 *    Contents/Resources/Base.lproj in the product directory which
 *    is something like
 *    ~/Library/Developer/Xcode/DerivedData/<product_name>-<some_string>/Build/Products/Debug/<product_name>.app
 *    You can use them to replace the .nib files in src/cocoa/en.lproj in the
 *    Angband source files.  In older versions of Angband, MainMenu.nib is a
 *    directory; you'll have to remove it and replace it with the flat file
 *    that is generated by the above procedure and adjust the installation
 *    rules for it in Makefile.osx.  With Xcode 13, the generated .nib files
 *    are back to being directories.  In the build results from that version
 *    of Xcode, copy Contents/Resources/Base.lproj/MainMenu.nib/keyedobjects.nib
 *    to replace src/cocoa/en.lproj/MainMenu.nib in the Angband source files
 *    and copy Contents/Resources/Base.lproj/TileSetScaling.nib/keyedobjects.nib
 *    to replace src/cocoa/en.lproj/TileSetScaling.nib (the
 *    keyedobjects-101300.nib files in the build results are for macOS 10.13
 *    or later).
 */

#import "AppDelegate.h"

@implementation AngbandAppDelegate

@synthesize commandMenu=_commandMenu;
@synthesize commandMenuTagMap=_comandMenuTagMap;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


/**
 * Implement the TileSetDefaultScalingComputing protocol.
 */
- (void)computeDefaultTileSetScaling:(NSInteger *)pHoriz vertical:(NSInteger *)pVert {
    *pHoriz = 1;
    *pVert = 1;
}

/**
 * Implement the TileSetScalingChanging protocol.
 */
- (void) changeTileSetScaling:(NSInteger)h vertical:(NSInteger)v isDefault:(BOOL)flag {
}

- (IBAction)newGame:(id)sender {
}

- (IBAction)editFont:(id)sender {
}

- (IBAction)openGame:(id)sender {
}

- (IBAction)saveGame:(id)sender {
}

- (IBAction)setRefreshRate:(NSMenuItem *)sender {
}

- (IBAction)showTileSetScalingPanel:(id)sender {
    if (self.scalingPanelController == nil) {
	self.scalingPanelController =
	    [[TileSetScalingPanelController alloc] initWithWindow:nil];

	self.scalingPanelController.defaultScalingComputer = self;
	self.scalingPanelController.scalingChangeHandler = self;
	self.scalingPanelController.usesDefaultScaling = YES;
    }
    [self.scalingPanelController showWindow:sender];
}

- (void)setGraphicsMode:(NSMenuItem *)sender {
}

- (void)selectWindow:(id)sender {
}

- (void)recomputeDefaultTileMultipliersIfNecessary {
}

- (void)beginGame {
}

@end
