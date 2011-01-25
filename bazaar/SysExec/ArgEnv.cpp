#include "ArgEnv.h"

NAMESPACE_UPP

///////////////////////////////////////////////////////////////////////////////////////////////
// parses an args line to be useable by spawnxx functions
Buffer<char *>BuildArgs(String const &command, String const &argline)
{
	Array<String> args;
	
	// first arg should be command name
	args.Add(command);

	// skips leading spaces
	char c;
	int pos = 0;
	while ((c = argline[pos]) != 0 && isspace(c))
		pos++;

	// loop reading args and putting to array
	while (c)
	{
		String &s = args.Add();
		while (c && !isspace(c))
		{
			// reads enquoted strings
			if (c == '"')
			{
				c = argline[++pos];
				while (c && c != '"')
				{
					s << c;
					c = argline[++pos];
				}
				if (c)
					c = argline[++pos];
			}
			else
			{
				s << c;
				c = argline[++pos];
			}
		}

		// skips trailing spaces
		while (c && isspace(c))
			c = argline[++pos];
	}
	
	// calculates buffer size (as byte)
	int buflen = 0;
	for(int i = 0; i < args.GetCount(); i++)
		buflen += args[i].GetCount() + 1;
	buflen += (args.GetCount() + 1) * sizeof(char *);
	
	// gets uprounded number of elements (as char *)
	if(buflen % sizeof(char *))
		buflen = buflen / sizeof(char *) + 1;
	else
		buflen /= sizeof(char *);

	// here we've got an array of args and the total size (in bytes) of them
	// we allocates a  buffer for arg array
	Buffer<char *>buf(buflen);

	// we fill the buffer with arg strings
	char **bufindex = buf;
	char *bufpos = (char *)(buf + args.GetCount() + 1);
	int i = 0;
	while (i < args.GetCount())
	{
		String s = args[i];
		strcpy(bufpos, ~s);
		*bufindex++ = bufpos;
		bufpos += s.GetCount() + 1 ;
		i++;
	}
	*bufindex = 0;

	// returns array of args
	return buf;

} // END _BuildArgs()


///////////////////////////////////////////////////////////////////////////////////////////////
// parses environment map and builds env array
Buffer<char *>BuildEnv(const VectorMap<String, String> &env)
{
	// calculates total environment size
	int envSize = 0;
	for (int i = 0; i < env.GetCount(); i++)
		envSize += env.GetKey(i).GetCount() + env[i].GetCount() + 2 + sizeof(char *);
	envSize+=2;

	// rounds buffer size at multiple of (char *)
	if(envSize % sizeof(char *))
		envSize += sizeof(char *) - (envSize % sizeof(char *));

	// gets uprounded number of elements (as char *)
	if(envSize % sizeof(char *))
		envSize = envSize / sizeof(char *) + 1;
	else
		envSize /= sizeof(char *);

	// we allocates a  buffer for env array
	Buffer<char *> buf(envSize);

	// we fill the buffer with env strings
	char **bufindex = buf;
	char *bufpos = (char *)(buf + env.GetCount() + 1);
	int i = 0;
	while (i < env.GetCount())
	{
		String s = env.GetKey(i) + "=" + env[i];
		strcpy(bufpos, ~s);
		*bufindex++ = bufpos;
		bufpos += s.GetCount() + 1 ;
		i++;
	}
	*bufindex = 0;

	// returns array of args
	return buf;

} // END _BuildEnv()

END_UPP_NAMESPACE
