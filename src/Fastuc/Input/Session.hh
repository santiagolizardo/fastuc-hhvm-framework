<?hh // strict
namespace Fastuc\Input;

class Session extends \Fastuc\Utils\TypedArray
{
	/**
	 * @param string $name
	 * @param array $params
	 */
	public function __construct( string $name = null, array $params = array() )
	{
		if( isset( $_SESSION ) )
		{
			trigger_error( 'Session can not be initialized twice.', E_USER_WARNING );
			return;
		}

		if( headers_sent() )
		{
			return;
		}

		if( isset( $params['iframeWorkaround'] ) )
		{
			header( 'P3P: CP="IDC DSP COR CURa DMa OUR IND PHY ONL COM STA"' );
		}

		$currentCookieParams = session_get_cookie_params();
		$currentCookieParams = array_merge( $currentCookieParams, $params );
		session_set_cookie_params(
			$currentCookieParams['lifetime'],
			$currentCookieParams['path'],
			$currentCookieParams['domain'],
			$currentCookieParams['secure'],
			$currentCookieParams['httponly']
		);

		if( !empty( $name ) )
		{
			session_name( $name );
		}

		if( false === session_start() )
		{
			throw new \Exception( 'Unable to create a new session.' );
		}

		$this->params = &$_SESSION;
	}

	/**
	 * @return bool
	 */
	public function destroy() : bool
	{
		return session_destroy();
	}
}

