<?hh // strict
namespace Fastuc\Services;

class Gravatar
{
	/**
	 * @param strig $email
	 * @param integer $size
	 * @param string $default
	 */
	public static function createImageUrl( $email, $size = 80, $default = null )
	{	
		$params = array( 's' => $size );
	
		if( null !== $default )
		{
			$inputServer = new \Fastuc\Input\Server;
			$defaultUrl = 'http://' . $inputServer->getParam( 'HTTP_HOST' ) . $default;
			$params['d'] = $defaultUrl;
		}

		$hash = md5( strtolower( trim( $email ) ) );
		
		return sprintf( 'http://www.gravatar.com/avatar/%s.jpg?%s', $hash, http_build_query( $params ) );
	} 
}

