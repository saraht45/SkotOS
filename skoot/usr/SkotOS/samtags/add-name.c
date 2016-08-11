/*
**	add-name.c
**
**	Adds a name to a specified detail.
*/
private inherit "/base/lib/urcalls";
private inherit "/lib/string";

inherit "/usr/SAM/lib/sam";
inherit "/usr/SkotOS/lib/describe";

# include <SAM.h>
# include "/usr/SAM/include/sam.h"

mixed tag_documentation(string type) {
   switch (type) {
   case "public":
      return TRUE;
   case "category":
      return "settings";
   case "description":
      return
	 "Add a singular or plural name to an object detail.  If the 'obj' " +
	 "parameter is an object, by default the primary detail will be used " +
	 "unless the 'detail' parameter is used as well.  You need to use at " +
	 "least one of 'name' and 'pname'.";
   case "required":
      return ([ "obj":  "The object or NRef in which to add the name." ]);
   case "optional":
      return ([ "detail": "The specific detail for which to add the name.  Only used if the 'obj' parameter isn't an NRef.",
		"name":   "An optional singular-name to add.",
		"pname":  "An optional plural-name to add." ]);
   default:
      return nil;
   }
}

int tag(mixed content, object context, mapping local, mapping args) {
   mixed ref;
   string id;
   object ob;

   AssertLocal("obj", "add-name");

   ref = local["obj"];

   if (local["name"] && typeof(local["name"]) != T_STRING) {
      error("SAM tag add-name requires a string for 'name'");
   }
   if (local["pname"] && typeof(local["pname"]) != T_STRING) {
      error("SAM tag add-name requires a string for 'pname'");
   }
   if (!local["name"] && !local["pname"]) {
      error("SAM tag add-name requires at least one of 'name' or 'pname'");
   }
   if (IsNRef(ref)) {
      id = NRefDetail(ref);
      ob = NRefOb(ref);
   } else {
      error("SAM tag add-name requires a NREF or OBJ for 'obj'.");
   }
   if (local["detail"]) {
      id = local["detail"];
   }

   /* call add_alias() */
   ob->add_alias(id, local["name"], local["pname"]);

   return TRUE;
}
