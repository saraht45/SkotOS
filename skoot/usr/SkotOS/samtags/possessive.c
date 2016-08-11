private inherit "/base/lib/urcalls";

inherit "/usr/SAM/lib/sam";
inherit "/usr/SkotOS/lib/describe";
inherit "/lib/string";

# include <SAM.h>
# include "/usr/SAM/include/sam.h"
# include <nref.h>

mixed tag_documentation(string type) {
   switch (type) {
   case "public":
      return TRUE;
   case "description":
      return "Get the possessive pronoun for the given item(s), which can be 'his', 'her', 'its', or 'their'.";
   case "required":
      return ([ "what": "The item(s) for which want to get the possessive pronoun." ]);
   case "optional":
      return ([ "cap": "Whether to capitalize the resulting output or not." ]);
   default:
      return nil;
   }
}

int tag(mixed content, object context, mapping local, mapping args) {
   mixed what;
   string res;

   AssertLocal("what", "possessive");

   what = local["what"];

   if (IsNRef(what))
      what = NRefOb(what);

   switch (typeof(what)) {
   case T_ARRAY:
       switch (sizeof(what)) {
       case 0:
  	   error("SAM tag 'possessive' requires an object or array as arg");
       case 1:
	   what = what[0];
	   if (IsNRef(what)) {
	       what = NRefOb(what);
	   }
	   res = what->query_possessive();
	   break;
       default:
	   res = "their";
	   break;
       }
       break;
   case T_OBJECT:
       res = what->query_possessive();
       break;
   default:
   	error("SAM tag 'possessive' requires an object or array as arg");
   }

   if (local["cap"]) {
      res = capitalize(res);
   }

   Output(res);

   return TRUE;
}

