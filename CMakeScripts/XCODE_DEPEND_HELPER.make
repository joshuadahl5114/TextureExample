# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.terrain_simple_texture.Debug:
/Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_7/terrain_simple_texture/Debug/terrain_simple_texture:
	/bin/rm -f /Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_7/terrain_simple_texture/Debug/terrain_simple_texture


PostBuild.terrain_simple_texture.Release:
/Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_7/terrain_simple_texture/Release/terrain_simple_texture:
	/bin/rm -f /Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_7/terrain_simple_texture/Release/terrain_simple_texture


PostBuild.terrain_simple_texture.MinSizeRel:
/Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_7/terrain_simple_texture/MinSizeRel/terrain_simple_texture:
	/bin/rm -f /Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_7/terrain_simple_texture/MinSizeRel/terrain_simple_texture


PostBuild.terrain_simple_texture.RelWithDebInfo:
/Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_7/terrain_simple_texture/RelWithDebInfo/terrain_simple_texture:
	/bin/rm -f /Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_7/terrain_simple_texture/RelWithDebInfo/terrain_simple_texture




# For each target create a dummy ruleso the target does not have to exist
