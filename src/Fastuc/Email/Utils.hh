<?hh // strict
namespace Fastuc\Email;

class Utils
{
	/**
	 * @param string $address
	 * @param string $name
	 * @return string
	 */
	public static function formatAddress( string $address, string $name = null ) : string
	{
		if( empty( $name ) )
		{
			return $address;
		}

		return sprintf( '%s <%s>', $name, $address );
	}
}

