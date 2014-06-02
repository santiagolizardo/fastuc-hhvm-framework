<?hh // strict
namespace Fastuc\Web;

/**
 * Redirects to different destinations and codes easily.
 */
class Redirector
{
	/**
	 * @var bool
	 */
	private bool $exitAfterRedirection;

	/**
	 * @var string
	 */
	private string $requestPath;

	/**
	 * @var string
	 */
	private string $contextPath;

	/**
	 * @param string $contextPath
	 */
	public function __construct( string $contextPath = '' )
	{
		$this->exitAfterRedirection = true;

		$this->contextPath = $contextPath;

		$requestUrl = parse_url( $_SERVER['REQUEST_URI'] );
		$this->requestPath = str_replace( $this->contextPath, '', $requestUrl['path'] );
	}

	/**
	 * @return string
	 */
	public function getContextPath() : string
	{
		return $this->contextPath;
	}

	/**
	 * @return string
	 */
	public function getRequestPath() : string
	{
		return $this->requestPath;
	}

	/**
	 * @param bool $exitAfterRedirection
	 */
	public function setExitAfterRedirection( bool $exitAfterRedirection )
	{
		$this->exitAfterRedirection = $exitAfterRedirection;
	}

	/**
	 * Redirects the application to the given URL, it also ends the current request.
	 *
	 * @param string $url The destination URL.
	 * @param bool $permanent Indicates whether if it is a permanent or temporary redirection.
	 */
	public function goToUrl( string $url, bool $permanent = false )
	{
		if( $this->isRelative( $url ) )
		{
			$url = $this->contextPath . $url;
		}

		if( $permanent )
		{
			$this->sendHeader( 'HTTP/1.1 301 Moved Permanently' );
		}

		if( empty( $url ) )
		{
			$url = '/';
		}

		$this->sendHeader( 'Location: ' . $url );

		if( $this->exitAfterRedirection )
		{
			exit( 0 );
		}
	}

	/**
	 * Redirects to the previous page.
	 *
	 * @param bool $permanent Indicates whether if a permanent or temporary redirection.
	 */
	public function goToReferer( bool $permanent = false )
	{
		$url = '/';

		// Go to referer only if the referer header exists and is a URL in the same domain.
		if( isset( $_SERVER['HTTP_REFERER'] ) && strpos( $_SERVER['HTTP_REFERER'], $_SERVER['HTTP_HOST'] ) )
		{
			$url = $_SERVER['HTTP_REFERER'];
		}

		$this->goToUrl( $url, $permanent );
	}

	/**
	 * @param string $url
	 * @return bool
	 */
	public function isRelative( string $url ) : bool
	{
		return substr( $url, 0, 7 ) != 'http://';
	}

	/**
	 * Redirects to an specific URL if one of the pattern matches.
	 *
	 * @param array patterns
	 */
	public function goToUrlIfMatches( array $patterns ) : void
	{
		foreach( $patterns as $pattern => $options )
		{
			$rePattern = '#^' . $pattern . '$#';
			if( preg_match( $rePattern, $this->requestPath, $matches ) )
			{
				$newUrl = preg_replace( $rePattern, $options[1], $this->requestPath );
				
				$this->goToUrl( $newUrl, 301 === $options[0] );
			}
		}
	}

	public function sendHeader( /* string */ $header ) : void
	{
		header( $header );
	}
}

