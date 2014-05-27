<?hh // strict
namespace Fastuc\Http;

interface RequestListener
{
	public function onHttpRequest( string $url );
}

