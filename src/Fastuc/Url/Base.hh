<?hh // strict
namespace Fastuc\Url;

class Base
{
	/**
	 * @var string
	 */
	private string $contextPath;

	/**
	 * @var \Fastuc\Web\Router
	 */
	private \Fastuc\Web\Router $webRouter;

	public function __construct()
	{
		try
		{
			$configFile = new \Fastuc\Config\File( 'routes' );
			$routes = $configFile->getValue();
		}
		catch( \Exception $e )
		{
			$routes = array();
		}

		$this->webRouter = new \Fastuc\Web\Router( $routes );

		$registry = \Fastuc\Registry::getInstance();
		$this->contextPath = $registry->hasParam( 'contextPath' ) ? $registry->getParam( 'contextPath' ) : '';
	}

	/**
	 * @param string $name
	 * @param array $params
	 * @param bool $absolute
	 */
	public function create( string $name, array $params = array(), bool $absolute = false ) : string
	{
		$params += array( 'IGNORE' => '' );

		$prefix = $suffix = '';

		if( $this->webRouter->exists( $name ) )
		{
			$route = $this->webRouter->get( $name );

			if( !empty( $route->getDomain() ) )
			{
				$prefix = 'http://' . $route->getDomain();
			}
			elseif( $absolute )
			{
				$prefix = 'http://' . $_SERVER['HTTP_HOST'];
			}

			$suffix = $route->getPathMatcher();
			$suffix = ltrim( $suffix, '^' );
			$suffix = rtrim( $suffix, '$' );
			$suffix = $this->contextPath . '/' . $suffix;
		}
		else
		{
			if( $absolute )
			{
				$prefix = 'http://' . $_SERVER['HTTP_HOST'];
			}

			$suffix = $this->contextPath . '/' . $name;
		}

		$url = $prefix . $suffix;
		$url = stripslashes( $url );

		$patternParams = $params;
		foreach( $patternParams as $key => $value )
		{
			$token = '/\(\?!?<' . $key . '>[^)]+\)/';
			if( preg_match( $token, $url ) )
			{
				unset( $params[ $key ] );
				$url = preg_replace( $token, $value, $url );
			}
		}

		preg_match_all( '/\(\?<([^>]+)>[^)]+\)/', $url, $matches );
		$detectedParams = !empty( $matches[1] ) ? $matches[1] : array();
		if( count( $detectedParams ) > 0 )
		{
			$missingParams = implode( ', ', $matches[1] );
			trigger_error( 'Missing parameters: ' . $missingParams, E_USER_NOTICE );
			throw new \Exception( 'Missing parameters: ' . $missingParams );
		}

		unset( $params['IGNORE'] );

		if( count( $params ) > 0 )
		{
			$url .= '?' . http_build_query( $params );
		}

		return $url;
	}
}

