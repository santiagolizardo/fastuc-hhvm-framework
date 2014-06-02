<?hh // strict
namespace Fastuc\Utils;

class Network
{
	/**
	 * @param array $serverVars
	 * @return string
	 */
	public static function getCurrentUrl( array $serverVars = null ) : string
	{
		if( null === $serverVars )
		{
			$serverVars = $_SERVER;
		}

		$url = 'http';

		if( !empty( $serverVars['HTTPS'] ) )
		{
			$url .= 's';
		}
		$url .= '://' . $serverVars['HTTP_HOST'];

		if( $serverVars['SERVER_PORT'] != 80 )
		{
			$url .= ':' . $serverVars['SERVER_PORT'];
		}

		$url .= $serverVars['REQUEST_URI'];

		return $url;		
	}
	
	/**
	 * @param array $serverVars
	 * @return string
	 */
	public static function getClientIp( array $serverVars = null ) : string
	{
		if( null === $serverVars )
		{
			$serverVars = $_SERVER;
		}

		$keys = array( 'HTTP_CLIENT_IP', 'HTTP_X_FORWARDED_FOR', 'HTTP_X_FORWARDED', 'HTTP_X_CLUSTER_CLIENT_IP', 'HTTP_FORWARDED_FOR', 'HTTP_FORWARDED', 'REMOTE_ADDR' );
		foreach ( $keys as $key )
		{
			if( array_key_exists( $key, $serverVars ) === true )
			{
				foreach( explode( ',', $serverVars[ $key ] ) as $ip )
				{
					if( filter_var( $ip, FILTER_VALIDATE_IP ) !== false )
					{
						return $ip;
					}
				}
			}
		}
	}
}

